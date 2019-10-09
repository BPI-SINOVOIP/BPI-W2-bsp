EXTRA_CFLAGS += -I ../core/

mars_scd-objs = scd_mars.o \
                scd_mars_priv.o

#obj-$(CONFIG_MARS_SMARTCARD_IFD) += mars_scd.o
obj-y				 += mars_scd.o


gpio_scd-objs = scd_gpio.o \
                scd_gpio_priv.o

obj-$(CONFIG_GPIO_SMARTCARD_IFD) += gpio_scd.o

icam_scd-objs = scd_icam.o \
                scd_icam_priv.o

obj-$(CONFIG_ICAM_SMARTCARD_IFD) += icam_scd.o

