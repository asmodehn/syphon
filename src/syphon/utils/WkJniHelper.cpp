#include "WkCocos/Utils/WkJniHelper.h"

#include "cocos/cocos2d.h"

//cocos style platform detection
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

#include "WkPlatform_WkCocos.h"

#endif

namespace WkCocos
{
	namespace Utils
	{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        jobject WkJniHelper::getInstance()
        {
            jobject instance;
            cocos2d::JniMethodInfo j_getInstanceMI;
            std::string clss = std::string(JAVA_PACKAGE) + "/WkJniHelper";
            std::string clss_prm = "()L" + clss + ";";
			CCLOG("Calling %s/getInstance%s", clss.c_str(), clss_prm.c_str());
			if (cocos2d::JniHelper::getStaticMethodInfo(j_getInstanceMI, clss.c_str(), "getInstance", clss_prm.c_str()))
			{
				instance = j_getInstanceMI.env->CallStaticObjectMethod(j_getInstanceMI.classID, j_getInstanceMI.methodID);
			}
			j_getInstanceMI.env->DeleteLocalRef(j_getInstanceMI.classID);
			return instance;
        }

        jobject WkJniHelper::getPushNotificationManager()
        {
            jobject instance;
            cocos2d::JniMethodInfo j_getPNMgrMI;

			jobject helperinst = WkJniHelper::getInstance();
			std::string hclss = std::string(JAVA_PACKAGE) + "/WkJniHelper";
            std::string pnclss = std::string(JAVA_PACKAGE) + "/PushNotificationsManager";
            std::string pnclss_prm = "()L" + pnclss + ";";
			CCLOG("Calling %s/getPNMgr%s", hclss.c_str(), pnclss_prm.c_str());
			if (helperinst && cocos2d::JniHelper::getMethodInfo(j_getPNMgrMI, hclss.c_str(), "getPNMgr", pnclss_prm.c_str()))
            {
                instance = j_getPNMgrMI.env->CallObjectMethod(helperinst, j_getPNMgrMI.methodID);
            }
            j_getPNMgrMI.env->DeleteLocalRef(helperinst);

			return instance;
        }

        jobject WkJniHelper::getAppMainActivity()
        {
            jobject instance;
            cocos2d::JniMethodInfo j_getMainActivityMI;

			jobject helperinst = WkJniHelper::getInstance();
            std::string clss = std::string(JAVA_PACKAGE) + "/WkJniHelper";
			CCLOG("Calling %s/getAppMainActivity()Landroid/app/Activity;",clss.c_str());
			if (helperinst && cocos2d::JniHelper::getMethodInfo(j_getMainActivityMI, clss.c_str(), "getAppMainActivity", "()Landroid/app/Activity;"))
            {
                instance = j_getMainActivityMI.env->CallObjectMethod(helperinst, j_getMainActivityMI.methodID);
            }
            j_getMainActivityMI.env->DeleteLocalRef(helperinst);

			return instance;
        }

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
//??
#endif

        std::string WkJniHelper::getVersionName()
        {
            std::string version = "";

            //platform detection based on cocos
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            //getting apk version name ( from Android code )

            cocos2d::JniMethodInfo j_getVNameMI;

            jobject instance = getAppMainActivity();

            std::string logstr = std::string("Calling ") + std::string(JAVA_PACKAGE) + std::string("/MainActivity/getVersionName()Ljava/lang/String;");
            CCLOG("%s",logstr.c_str());
            std::string MainActivityStr = std::string(JAVA_PACKAGE) + std::string("/MainActivity");
            if (instance && cocos2d::JniHelper::getMethodInfo(j_getVNameMI, MainActivityStr.c_str() , "getVersionName", "()Ljava/lang/String;"))
            {
                jobject jvername = j_getVNameMI.env->CallObjectMethod(instance, j_getVNameMI.methodID);

                const char* jvernamecstr = j_getVNameMI.env->GetStringUTFChars((jstring)jvername, NULL);
                version.assign(jvernamecstr);
                j_getVNameMI.env->ReleaseStringUTFChars((jstring)jvername, jvernamecstr);

                j_getVNameMI.env->DeleteLocalRef(j_getVNameMI.classID);
                j_getVNameMI.env->DeleteLocalRef(jvername);
            }
#endif
            CCLOG("Version detected : %s", version.c_str());
            return version;
		}

		void WkJniHelper::openURL(std::string url)
		{
			//TODO : change to match design using WkJniHelpers
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			cocos2d::JniMethodInfo minfo;
			std::string clss = std::string(JAVA_PACKAGE) + "/MainActivity";

            if (cocos2d::JniHelper::getStaticMethodInfo(minfo, clss.c_str(), "openURL", "(Ljava/lang/String;)V")) {
                jstring StringArg1 = minfo.env->NewStringUTF(url.c_str());
                minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
                minfo.env->DeleteLocalRef(StringArg1);
                minfo.env->DeleteLocalRef(minfo.classID);
            }
#else
			//TODO
#endif
		}

		void WkJniHelper::showAd(cocos2d::Vec2 pos)
		{
			//TODO : change to match design using WkJniHelpers
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			cocos2d::JniMethodInfo j_getMainActivityMI;

			jobject helperinst = WkJniHelper::getInstance();
            std::string clss = std::string(JAVA_PACKAGE) + "/WkJniHelper";
			CCLOG("Calling %s/showAdBanner(II)V", clss.c_str());
			if (helperinst && cocos2d::JniHelper::getMethodInfo(j_getMainActivityMI, clss.c_str(), "showAdBanner", "(II)V"))
			{
				jint x = static_cast<int>(pos.x);
				jint y = static_cast<int>(pos.y);
				j_getMainActivityMI.env->CallVoidMethod(helperinst, j_getMainActivityMI.methodID, x, y);
			}
			j_getMainActivityMI.env->DeleteLocalRef(helperinst);
#else
			//TODO
#endif
		}

		void WkJniHelper::hideAd()
		{
			//TODO : change to match design using WkJniHelpers
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			cocos2d::JniMethodInfo j_getMainActivityMI;

			jobject helperinst = WkJniHelper::getInstance();
            std::string clss = std::string(JAVA_PACKAGE) + "/WkJniHelper";
			CCLOG("Calling %s/hideAdBanner()V", clss.c_str());
			if (helperinst && cocos2d::JniHelper::getMethodInfo(j_getMainActivityMI, clss.c_str(), "hideAdBanner", "()V"))
			{
				j_getMainActivityMI.env->CallVoidMethod(helperinst, j_getMainActivityMI.methodID);
			}
			j_getMainActivityMI.env->DeleteLocalRef(helperinst);
#else
			//TODO
#endif
		}

		void WkJniHelper::showInterstitialAd()
		{
			//TODO : change to match design using WkJniHelpers
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			cocos2d::JniMethodInfo j_getMainActivityMI;

			jobject helperinst = WkJniHelper::getInstance();
            std::string clss = std::string(JAVA_PACKAGE) + "/WkJniHelper";
			CCLOG("Calling %sshowInterstitialAd()", clss.c_str());
			if (helperinst && cocos2d::JniHelper::getMethodInfo(j_getMainActivityMI, clss.c_str(), "showInterstitialAd", "()V"))
			{
				j_getMainActivityMI.env->CallVoidMethod(helperinst, j_getMainActivityMI.methodID);
			}
			j_getMainActivityMI.env->DeleteLocalRef(helperinst);
#else
			//TODO
#endif
		}

	}
}

