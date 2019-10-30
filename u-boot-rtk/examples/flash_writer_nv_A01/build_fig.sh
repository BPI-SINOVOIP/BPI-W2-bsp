#!/bin/bash
TEMP=FIG_temp
OUT=FIG_out
TOOLPATH=tools/script
CUR=$(pwd)
SELECTION=`cat $1 | awk 'BEGIN { FS="= 0x" };/SCS_Total_Area_Size_Selection/{ print $2}'`
AREA_SIZE_VAR="SCS_Total_Area_Size_$SELECTION"
MAX_AREA_SIZE_VAR="SCS_Total_Area_Size_4"
AREA_SIZE=`cat $1 | awk 'BEGIN { FS="= " };/'$AREA_SIZE_VAR'/{ print $2}'`
MAX_AREA_SIZE=`cat $1 | awk 'BEGIN { FS="= " };/'$MAX_AREA_SIZE_VAR'/{ print $2}'`
PADDING_SIZE=$(($MAX_AREA_SIZE - $AREA_SIZE))

mkdir -p $OUT
mkdir -p $TEMP

echo "SCS_Total_Area_Size_Selection:" $SELECTION
echo "SCS_Total_Area_Size_$SELECTION:" $AREA_SIZE
echo "SCS_Total_Area_Size_4:" $MAX_AREA_SIZE
echo "padding_size:" $PADDING_SIZE
echo gen_fig
cd tools/script
./gen_fig.sh $PADDING_SIZE
cd ../..
cp $CUR/Bind/FIG.bin $OUT/RTK_RTD1611_A2_LE_RefImgSizeA.bin


pushd $TOOLPATH/FIG
echo do_partSha
./do_partSha $CUR/Bind/Auxcode_body.bin $CUR/$TEMP/sha256.bin
./do_partSha $CUR/Bind/Auxcode_body.bin $CUR/$OUT/RTK_RTD1611_A2_SCSAuxiliaryCode_PartialHash_LE.bin

echo do_sha256
./do_sha256 $CUR/Bind/Auxcode_Area.bin.tmp2 $CUR/$TEMP/sha256.bin $CUR/$TEMP/out.bin

echo gen_signature.sh
./gen_signature.sh $CUR/Bind/Auxcode_Area.bin.tmp2 $CUR/$TEMP/sha256.bin $CUR/image/rsa_key_2048.tee.pem

echo compute sha256 of Auxcode_Area2.bin
cat $CUR/Bind/Auxcode_Area2.bin | openssl dgst -sha256

popd

rm $TEMP -rf


