# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := native-activity
LOCAL_SRC_FILES := main.cpp App.cpp Asteroids.cpp Asteroid.cpp Player.cpp Dimensions.cpp Bullet.cpp Bullets.cpp SpliceAsteroids.cpp LevelProgress.cpp DecorateStar.cpp DecorateStars.cpp Graphics.cpp CometTail.cpp ScreenShaker.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_CFLAGS :=-D__GXX_EXPERIMENTAL_CXX0X__
LOCAL_CPPFLAGS  := -std=c++11

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
