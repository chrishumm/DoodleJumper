LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/menuScene.cpp \
				   ../../Classes/menuLayer.cpp \
				   ../../Classes/levelLayer.cpp \
				   ../../Classes/levelScene.cpp \
				   ../../Classes/endLayer.cpp \
				   ../../Classes/endScene.cpp \
				   ../../Classes/devNameLayer.cpp \
				   ../../Classes/world_object.cpp \
				   ../../Classes/platformClass.cpp \
				   ../../Classes/playerClass.cpp \
				   ../../Classes/hudLayer.cpp \
				   ../../Classes/GLES-Render.cpp \
				   ../../Classes/B2DebugDrawLayer 
				   
				   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
