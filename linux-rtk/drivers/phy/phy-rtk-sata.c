#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/reset.h>
#include <linux/phy/phy.h>
#include <linux/delay.h>

#include <soc/realtek/rtk_chip.h>

#define RTK_SATA_PHY_NUMBER	2
#define DEFAULT_TXDRV_LEVEL	3
#define PHY_MAX_CLK		5
#define PHY_MAX_RST		5

#define PHY_CLK_EN		0x18
#define MDIO_CTR		0x60
#define MDIO_CTR1		0x64
#define PHY_SPD			0x68

struct phy_rtk_desc {
	unsigned int index;
	unsigned int param_size;
	unsigned int *param_table;
	unsigned int txdrv_size;
	unsigned int *txdrv_table;
	unsigned int rxsense_size;
	unsigned int *rxsense_table;
	unsigned int ssc_en;
	unsigned int speed;
	struct phy *phy;
	struct reset_control *rsts[PHY_MAX_RST];
};

struct phy_rtk_priv {
	void __iomem *base;
	void __iomem *sb2base;
	struct clk *clks[PHY_MAX_CLK];
	struct reset_control *rsts[PHY_MAX_RST];
	struct phy_rtk_desc **phys;
	struct device *dev;
	unsigned int nphys;
	enum rtd_chip_id chip_id;
	enum rtd_chip_revision chip_revision;
};

static const unsigned int PHY_PARA_TABLE[] = {
	0x00001111, 0x00005111, 0x00009111,
	0x336a0511, 0x336a4511, 0x336a8511,
	0xE0700111, 0xE05C4111, 0xE04A8111,
	0x00150611, 0x00154611, 0x00158611,
	0xC6000A11, 0xC6004A11, 0xC6008A11,
	0x70000211, 0x70004211, 0x70008211,
	0xC6600A11, 0xC6604A11, 0xC6608A11,
	0x20041911, 0x20045911, 0x20049911,
	0x94aa2011, 0x94aa6011, 0x94aaa011,
	0x17171511, 0x17175511, 0x17179511,
	0x07701611, 0x07705611, 0x07709611,
	0x40002a11, 0x40006a11, 0x4000aa11,
	0x29001011, 0x29005011, 0x29009011,
	0x40000C11, 0x40004C11, 0x40008C11,
	0x00271711, 0x00275711, 0x00279711,
};

static const unsigned int TX_DRV_TABLE[][6] = {
	//max_500mV
	{ 0x94a52011, 0x94a56011, 0x94a5a011,
		0x385a2111, 0x385a6111, 0x385aa111 },
	//max_573mV
	{ 0x94a62011, 0x94a66011, 0x94a6a011,
		0x486a2111, 0x486a6111, 0x486aa111 },
	//max_683mV
	{ 0x94a72011, 0x94a76011, 0x94a7a011,
		0x587a2111, 0x587a6111, 0x587aa111 },
	//max_786mV
	{ 0x94aa2011, 0x94aa6011, 0x94aaa011,
		0x88aa2111, 0x88aa6111, 0x88aaa111 },
	//max_786mV
	{ 0x94aa2011, 0x94aa6011, 0x94aaa011,
		0x88aa2111, 0x88aa6111, 0x88aaa111 },
	//max_786mV
	{ 0x94aa2011, 0x94aa6011, 0x94aaa011,
		0x88aa2111, 0x88aa6111, 0x88aaa111 },
	//max_786mV
	{ 0x94aa2011, 0x94aa6011, 0x94aaa011,
		0x88aa2111, 0x88aa6111, 0x88aaa111 },
	//max_786mV
	{ 0x94aa2011, 0x94aa6011, 0x94aaa011,
		0x88aa2111, 0x88aa6111, 0x88aaa111 },
};

static const unsigned int PHY_SENSITIVITY[][6] = {
	{ 0x72100911, 0x72104911, 0x72108911,
		0x27730311, 0x27684311, 0x27688311 },
	{ 0x42100911, 0x42104911, 0x42108911,
		0x276f0311, 0x276d4311, 0x276d8311 },
	{ 0x42100911, 0x42104911, 0x42108911,
		0x276a0311, 0x276a4311, 0x27688311 },
};

static const unsigned int SSCEN_SET_TABLE[] = {
	0x738E0411, 0x738E0411, 0x738E8411,
	0x35910811, 0x35914811, 0x35918811,
	0x02342711, 0x02346711, 0x0234a711,
};

static const unsigned int SSCDIS_SET_TABLE[] = {
	0x538E0411, 0x538E4411, 0x538E8411,
};

static const unsigned int PHY_CLOCK_DELAY[] = {
	0x7c002a11, 0x7c006a11, 0x7c00aa11,
};

static const unsigned int PHY_PARA_TABLE_THOR[] = {
	0x70000211, 0x70004211, 0x70008211,
	0x336a0511, 0x336a4511, 0x336a8511,
	0xa9040b11, 0xa9044b11, 0xa9048b11,
	0x500b1411, 0x500b5411, 0x500b9411,
	0x77771511, 0x77775511, 0x77779511,
	0x00231711, 0x00235711, 0x00239711,
	0x00632211, 0x00636211, 0x0063a211,
	0xab762311, 0xab766311, 0xab76a311,
};

static const unsigned int TX_DRV_TABLE_THOR[][6] = {
	{ 0x40aa2011, 0x40aa6011, 0x40a8a011,
		0x88aa2111, 0x88aa6111, 0x88aaa111 },
};

static int write_mdio_reg(unsigned int value, void __iomem *address)
{
	unsigned int cnt = 0;

	while (readl(address) & 0x80) {
		udelay(10);
		cnt++;
		if (cnt > 5) {
			pr_err("sata %s fail\n", __func__);
			return -1;
		}
	}
	writel(value, address);

	return 0;
}

static unsigned int read_mdio_reg(unsigned int reg, void __iomem *address)
{
	unsigned int value;

	value = (reg << 8) | 0x10;
	write_mdio_reg(value, address);

	value = readl(address);
	return value;
}

static struct phy *phy_rtk_sata_xlate(struct device *dev,
					struct of_phandle_args *args)
{
	struct phy_rtk_priv *priv = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < priv->nphys; i++)
		if (priv->phys[i]->index == args->args[0])
			break;

	if (i == priv->nphys)
		return ERR_PTR(-ENODEV);

	return priv->phys[i]->phy;
}

static int phy_rtk_sata_init(struct phy *phy)
{
	struct phy_rtk_desc *desc = phy_get_drvdata(phy);
	struct phy_rtk_priv *priv = dev_get_drvdata(phy->dev.parent);
	void __iomem *base = priv->base;
	void __iomem *sb2base = priv->sb2base;
	unsigned int *table;
	unsigned int reg;
	int i;
	unsigned int size;

	if (priv->chip_id == CHIP_ID_RTD1619 ||
		priv->chip_id == CHIP_ID_RTD1319) {
		for (i=0; i<PHY_MAX_RST; i++) {
			if (desc->rsts[i] == NULL)
				break;
			reset_control_deassert(desc->rsts[i]);
		}
	}

	reg = readl(sb2base);
	if (desc->index == 0)
		reg = reg | BIT(0) | BIT(2) | BIT(4) | BIT(8);
	else
		reg = reg | BIT(1) | BIT(3) | BIT(5);
	writel(reg, sb2base);

	writel(desc->index, base + MDIO_CTR1);

	for (i = 0; i < desc->param_size; i++) {
		dev_info(priv->dev, "phy%d para 0x%x\n", desc->index, desc->param_table[i]);
		write_mdio_reg(desc->param_table[i], base + MDIO_CTR);
	}
	for (i = 0; i < desc->txdrv_size; i++) {
		dev_info(priv->dev, "phy%d txdrv 0x%x\n", desc->index, desc->txdrv_table[i]);
		write_mdio_reg(desc->txdrv_table[i], base + MDIO_CTR);
	}

	for (i = 0; i < desc->rxsense_size; i++) {
		dev_info(priv->dev, "phy%d rxsense 0x%x\n", desc->index, desc->rxsense_table[i]);
		write_mdio_reg(desc->rxsense_table[i], base + MDIO_CTR);
	}

	if (priv->chip_id != CHIP_ID_RTD1619 ||
		priv->chip_id != CHIP_ID_RTD1319) {
		if (desc->ssc_en) {
			table = (unsigned int *)&SSCEN_SET_TABLE;
			size = sizeof(SSCEN_SET_TABLE)/sizeof(unsigned int);
		} else {
			table = (unsigned int *)&SSCDIS_SET_TABLE;
			size = sizeof(SSCDIS_SET_TABLE)/sizeof(unsigned int);
		}
		for (i = 0; i < size; i++)
			write_mdio_reg(table[i], base + MDIO_CTR);

		if ((priv->chip_id & 0xFFF0) == CHIP_ID_RTD129X &&
			priv->chip_revision == RTD_CHIP_B00) {
			table = (unsigned int *)&PHY_CLOCK_DELAY;
			size = sizeof(PHY_CLOCK_DELAY)/sizeof(unsigned int);
			for (i = 0; i < size; i++)
				write_mdio_reg(table[i], base + MDIO_CTR);
		}
	}

	if (desc->speed == 0)
		writel(0xA, base + PHY_SPD);
	else if (desc->speed == 2)
		writel(0x5, base + PHY_SPD);
	else if (desc->speed == 1)
		writel(0x0, base + PHY_SPD);

	if (priv->chip_id == CHIP_ID_RTD1319) {
		reg = readl(base + PHY_CLK_EN) | (1 << (desc->index+7));
		writel(reg, base + PHY_CLK_EN);
	}
	dev_info(priv->dev, "init phy%d OK\n", desc->index);

	return 0;
}

static int phy_rtk_sata_power_on(struct phy *phy)
{
	struct phy_rtk_desc *desc = phy_get_drvdata(phy);
	struct phy_rtk_priv *priv = dev_get_drvdata(phy->dev.parent);
	int i;

	dev_info(priv->dev, "power on phy%d\n", desc->index);

	for (i=0; i<PHY_MAX_RST; i++) {
		if (desc->rsts[i] != NULL)
			reset_control_deassert(desc->rsts[i]);
		else
			break;
	}
	return 0;
}

static int phy_rtk_sata_power_off(struct phy *phy)
{
	struct phy_rtk_desc *desc = phy_get_drvdata(phy);
	struct phy_rtk_priv *priv = dev_get_drvdata(phy->dev.parent);
	int i;

	dev_info(priv->dev, "power off phy%d\n", desc->index);

	for (i=0; i<PHY_MAX_RST; i++) {
		if (desc->rsts[i] != NULL)
			reset_control_assert(desc->rsts[i]);
		else
			break;
	}
	return 0;
}

static int phy_rtk_sata_set_mode(struct phy *phy, enum phy_mode mode)
{
	struct phy_rtk_desc *desc = phy_get_drvdata(phy);
	struct phy_rtk_priv *priv = dev_get_drvdata(phy->dev.parent);
	void __iomem *base = priv->base;
	unsigned int value;
	int i;

	if (priv->chip_id == CHIP_ID_RTD1619 ||
		priv->chip_id == CHIP_ID_RTD1319) {
		writel(desc->index, base + MDIO_CTR1);
		for (i=0; i<3; i++) {
			value = read_mdio_reg(0x20+0x40*i, base + MDIO_CTR);
			if (mode)
				value = value | (0x3 << 28);
			else
				value = value & ~(0x3 << 28);
			value = value | 0x11;
			write_mdio_reg(value, base + MDIO_CTR);

			value = read_mdio_reg(0x2a+0x40*i, base + MDIO_CTR);
			if (mode)
				value = value & ~(0x1 << 23);
			else
				value = value | (0x1 << 23);
			value = value | 0x11;
			write_mdio_reg(value, base + MDIO_CTR);
		}
	} else {
		for (i=0; i<PHY_MAX_RST; i++) {
			if (desc->rsts[i] != NULL && mode)
				reset_control_assert(desc->rsts[i]);
			else if (desc->rsts[i] != NULL && !mode)
				reset_control_deassert(desc->rsts[i]);
			else
				break;
		}
	}
	return 0;
}

static struct phy_ops phy_rtk_sata_ops = {
	.init = phy_rtk_sata_init,
	.power_on = phy_rtk_sata_power_on,
	.power_off = phy_rtk_sata_power_off,
	.set_mode = phy_rtk_sata_set_mode,
	.owner = THIS_MODULE,
};

static int get_phy_parameter(struct device *dev, struct device_node *node,
				struct phy_rtk_desc *desc)
{
	struct phy_rtk_priv *priv = dev_get_drvdata(dev);
	const void *prop;
	unsigned int drv_level;
	unsigned int size;
	unsigned int *table;
	unsigned int num = 0;

	prop = of_get_property(node, "phy-param", NULL);
	if (!prop) {
		if (priv->chip_id == CHIP_ID_RTD1619 ||
			priv->chip_id == CHIP_ID_RTD1319)
			size = sizeof(PHY_PARA_TABLE_THOR)/sizeof(unsigned int);
		else
			size = sizeof(PHY_PARA_TABLE)/sizeof(unsigned int);
	} else {
		size = of_property_count_u32_elems(node, "phy-param");
	}

	table = devm_kzalloc(dev, sizeof(unsigned int)*size, GFP_KERNEL);
	if (!table)
		return -ENOMEM;
	if (!prop) {
		if (priv->chip_id == CHIP_ID_RTD1619 ||
			priv->chip_id == CHIP_ID_RTD1319)
			memcpy(table, &PHY_PARA_TABLE_THOR, sizeof(PHY_PARA_TABLE_THOR));
		else
			memcpy(table, &PHY_PARA_TABLE, sizeof(PHY_PARA_TABLE));
	} else {
		of_property_read_u32_array(node, "phy-param", table, size);
	}
	desc->param_size = size;
	desc->param_table = table;

	prop = of_get_property(node, "tx-driving-tbl", NULL);
	if (!prop)
		size = sizeof(*TX_DRV_TABLE)/sizeof(unsigned int);
	else
		size = of_property_count_u32_elems(node, "tx-driving-tbl");

	table = devm_kzalloc(dev, sizeof(unsigned int)*size, GFP_KERNEL);
	if (!table)
		return -ENOMEM;
	if (!prop) {
		if ((priv->chip_id & 0xFFF0) == CHIP_ID_RTD129X) {
			drv_level = DEFAULT_TXDRV_LEVEL;
			of_property_read_u32(node, "tx-driving", &drv_level);
			if (drv_level >= sizeof(TX_DRV_TABLE)/sizeof(*TX_DRV_TABLE))
				drv_level = DEFAULT_TXDRV_LEVEL;
			memcpy(table, TX_DRV_TABLE[drv_level], sizeof(*TX_DRV_TABLE));
		} else if (priv->chip_id == CHIP_ID_RTD1619 ||
				priv->chip_id == CHIP_ID_RTD1319) {
			dev_info(dev, "can't find tx table\n");
			drv_level = 0;
			memcpy(table, TX_DRV_TABLE_THOR[drv_level], sizeof(*TX_DRV_TABLE_THOR));
		}
	} else {
		of_property_read_u32_array(node, "tx-driving-tbl", table, size);
	}
	desc->txdrv_size = size;
	desc->txdrv_table = table;

	prop = of_get_property(node, "rx-sense-tbl", NULL);
	if (!prop) {
		size = sizeof(*PHY_SENSITIVITY)/sizeof(unsigned int);
	} else {
		size = of_property_count_u32_elems(node, "rx-sense-tbl");
	}

	table = devm_kzalloc(dev, sizeof(unsigned int)*size, GFP_KERNEL);
	if (!table)
		return -ENOMEM;
	if (!prop) {
		dev_info(dev, "can't find rx table\n");
		if ((priv->chip_id & 0xFFF0) == CHIP_ID_RTD129X) {
			if (priv->chip_revision == RTD_CHIP_A00 ||
				priv->chip_revision == RTD_CHIP_A01)
				num = 0;
			else
				num = 1;
		} else if (priv->chip_id == CHIP_ID_RTD1619 ||
				priv->chip_id == CHIP_ID_RTD1319) {
			num = 2;
		}
		memcpy(table, PHY_SENSITIVITY[num], sizeof(*PHY_SENSITIVITY));
	} else {
		of_property_read_u32_array(node, "rx-sense-tbl", table, size);
	}
	desc->rxsense_size = size;
	desc->rxsense_table = table;

	if (priv->chip_id == CHIP_ID_RTD1319)
		desc->rxsense_size = 0;

	of_property_read_u32(node, "spread-spectrum", &desc->ssc_en);
	of_property_read_u32(node, "speed-limit", &desc->speed);

	return 0;
}

static void phy_rtk_sata_enable(struct phy_rtk_priv *priv)
{
	int i;

	for (i=0; i<PHY_MAX_CLK; i++) {
		if (priv->clks[i] == NULL)
			break;
		clk_prepare_enable(priv->clks[i]);
	}
	for (i=0; i<PHY_MAX_RST; i++) {
		if (priv->rsts[i] == NULL)
			break;
		reset_control_deassert(priv->rsts[i]);
	}
}

static void phy_rtk_sata_disable(struct phy_rtk_priv *priv)
{
#ifdef DISABLE_CLKRST
	int i;

	for (i=0; i<PHY_MAX_RST; i++) {
		if (priv->rsts[i] == NULL)
			break;
		reset_control_assert(priv->rsts[i]);
	}
	for (i=0; i<PHY_MAX_CLK; i++) {
		if (priv->clks[i] == NULL)
			break;
		clk_disable_unprepare(priv->clks[i]);
	}
#endif
	return;
}

static int phy_rtk_sata_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *child;
	struct phy *phy;
	struct phy_rtk_priv *priv;
	struct phy_provider *phy_provider;
	struct clk *clk;
	struct reset_control *rst;

	unsigned int phy_id;
	unsigned int i = 0, cnt = 0;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		goto memalloc_fail;

	priv->chip_id = get_rtd_chip_id();
	priv->chip_revision = get_rtd_chip_revision();

	priv->base = of_iomap(dev->of_node, 0);
	if (!priv->base)
		goto dtb_fail;
	priv->sb2base = of_iomap(dev->of_node, 1);
	if (!priv->base)
		goto dtb_fail;

	for (i=0; i<PHY_MAX_CLK; i++) {
		clk = of_clk_get(dev->of_node, i);
		if (IS_ERR(clk))
			break;
		priv->clks[i] = clk;
	}
	for (i=0; i<PHY_MAX_RST; i++) {
		rst = of_reset_control_get_by_index(dev->of_node, i);
		if (IS_ERR(rst))
			break;
		priv->rsts[i] = rst;
	}
	phy_rtk_sata_enable(priv);

	priv->nphys = of_get_child_count(dev->of_node);
	if (priv->nphys == 0 || priv->nphys > RTK_SATA_PHY_NUMBER)
		return -ENODEV;

	priv->dev = dev;
	priv->phys =
		devm_kcalloc(dev, priv->nphys, sizeof(*priv->phys), GFP_KERNEL);
	if (!priv->phys)
		goto memalloc_fail;

	dev_set_drvdata(dev, priv);

	for_each_available_child_of_node(dev->of_node, child) {
		struct phy_rtk_desc *phy_desc;

		phy_desc = devm_kzalloc(dev, sizeof(*phy_desc), GFP_KERNEL);
		if (!phy_desc)
			goto memalloc_fail;

		if (of_property_read_u32(child, "reg", &phy_id))
			goto dtb_fail;

		if (phy_id >= RTK_SATA_PHY_NUMBER)
			goto dtb_fail;

		for (i=0; i<PHY_MAX_RST; i++) {
			rst = of_reset_control_get_by_index(child, i);
			if (IS_ERR(rst))
				break;
			phy_desc->rsts[i] = rst;
		}

		ret = get_phy_parameter(dev, child, phy_desc);
		if (ret < 0)
			goto memalloc_fail;

		phy = devm_phy_create(dev, NULL, &phy_rtk_sata_ops);
		if (IS_ERR(phy)) {
			dev_err(dev, "failed to create phy %d\n", phy_id);
			return PTR_ERR(phy);
		}

		phy_desc->phy = phy;
		phy_desc->index = phy_id;
		phy_set_drvdata(phy, phy_desc);
		priv->phys[cnt++] = phy_desc;
	}

	phy_provider = devm_of_phy_provider_register(dev, phy_rtk_sata_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);

dtb_fail:
	dev_err(dev, "[SATA_PHY] get resource from dtb fail\n");
	return -EINVAL;

memalloc_fail:
	dev_err(dev, "[SATA_PHY] can't allocate memory\n");
	return -ENOMEM;
}

#ifdef CONFIG_PM
static int phy_rtk_sata_suspend(struct device *dev)
{
	struct phy_rtk_priv *priv = dev_get_drvdata(dev);

	dev_info(dev, "enter %s\n", __func__);
	phy_rtk_sata_disable(priv);
	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static void phy_rtk_sata_shutdown(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct phy_rtk_priv *priv = dev_get_drvdata(dev);

	dev_info(dev, "enter %s\n", __func__);
	phy_rtk_sata_disable(priv);
	dev_info(dev, "exit %s\n", __func__);
	return;
}

static int phy_rtk_sata_resume(struct device *dev)
{
	struct phy_rtk_priv *priv = dev_get_drvdata(dev);

	dev_info(dev, "enter %s\n", __func__);
	phy_rtk_sata_enable(priv);
	dev_info(dev, "exit %s\n", __func__);

	return 0;

}

static const struct dev_pm_ops phy_rtk_sata_pm_ops = {
	.suspend = phy_rtk_sata_suspend,
	.resume = phy_rtk_sata_resume,
};
#else
static const struct dev_pm_ops phy_rtk_sata_pm_ops = {};
#endif

static const struct of_device_id phy_rtk_sata_of_match[] = {
	{ .compatible = "Realtek,rtk-sata-phy" },
	{ },
};

static struct platform_driver phy_rtk_sata_driver = {
	.probe	= phy_rtk_sata_probe,
#ifdef CONFIG_PM
	.shutdown = phy_rtk_sata_shutdown,
#endif
	.driver	= {
		.name		= "phy-rtk-sata",
		.of_match_table	= phy_rtk_sata_of_match,
#ifdef CONFIG_PM
		.pm = &phy_rtk_sata_pm_ops,
#endif
	},
};
module_platform_driver(phy_rtk_sata_driver);

MODULE_DESCRIPTION("Realtek SATA PHY driver");
MODULE_AUTHOR("Simon HSU <simon_hsu@realtek.com>");
MODULE_LICENSE("GPL v2");
