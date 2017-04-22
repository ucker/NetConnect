include $(TOPDIR)/rules.mk

PKG_NAME:=NetConnect
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk


define Package/NetConnect
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=NetConnect
endef

define Build/Prepare
	$(MKDIR) -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		LIBS="" \
		LDFLAGS="$(EXTRA_LDFLAGS)" \
		CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CPPFLAGS)" \
		$(TARGET_CONFIGURE_OPTS) \
		CROSS="$(TARGET_CROSS)" \
		ARCH="$(ARCH)" \
		$(1);
endef

define Package/NetConnect/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/NetConnect $(1)/bin/

	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(TOOLCHAIN_DIR)/lib/libstdc++.so.6 $(1)/usr/lib
	$(INSTALL_DATA) $(TOOLCHAIN_DIR)/lib/libc.so $(1)/usr/lib/libc.so
	$(INSTALL_DATA) $(TOOLCHAIN_DIR)/lib/libgcc_s.so.1 $(1)/usr/lib/libgcc_s.so.1
	$(INSTALL_DATA) $(TOOLCHAIN_DIR)/usr/lib/libcrypto.so.1.0.0 $(1)/usr/lib
	$(INSTALL_DATA) $(TOOLCHAIN_DIR)/usr/lib/libssl.so.1.0.0 $(1)/usr/lib
endef

$(eval $(call BuildPackage,NetConnect))
