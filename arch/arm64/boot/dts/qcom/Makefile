ifeq ($(CONFIG_BUILD_ARM64_DT_OVERLAY),y)

dtbo-$(CONFIG_ARCH_SDM632) += \
	sdm450-mtp-s3-overlay.dtbo

sdm450-mtp-s3-overlay.dtbo-base := \
	sdm632.dtb

else
$(error Builds without CONFIG_BUILD_ARM64_DT_OVERLAY are not supported. In Android builds this is enabled from device/fairphone/FP3/AndroidBoard.mk)
endif

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb
