#!/bin/sh
export QT_QPA_PLATFORM='linuxfb:fb=/dev/fb0'
export QT_PLUGIN_PATH='./qt/plugins'
export QT_QPA_PLATFORM_PLUGIN_PATH='./qt/plugins'
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./:./qt/lib:./qt/plugins/platforms
export QT_QPA_FONTDIR=./qt/font/freefont
