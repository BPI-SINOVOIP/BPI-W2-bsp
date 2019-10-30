pushd "../../Bind" > /dev/null
#dd if=/dev/zero of=./SCS_Unchecked_Area.bin bs=4K count=1
#dd if=/dev/zero of=./Padding.bin bs=872448 count=1
echo "padding_size:" $1
dd if=/dev/zero bs=4K count=1 | tr "\000" "\377" > SCS_Unchecked_Area.bin
dd if=/dev/zero bs=$1 count=1 | tr "\000" "\377" > Padding.bin
cat Auxcode_Area.bin Auxcode_Area_RTK_digest_enc.bin > Auxcode_body.bin
cat NOCS_Certificate_final.bin SCS_Params_Area_final.bin Auxcode_Area_final.bin DTE_Bootcode_Area_final.bin SCS_Unchecked_Area.bin > FIG1.bin
cat FIG1.bin Padding.bin PCPU_Certificate_final.bin PCPU_Code_Area_final.bin > FIG.bin
ls FIG1.bin -la
ls FIG.bin -la
ls Auxcode_body.bin -la
popd > /dev/null
