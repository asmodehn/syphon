#ifndef __DFGAME_DOWNLOAD_ENTITY_COMP_FILEMD5_H__
#define __DFGAME_DOWNLOAD_ENTITY_COMP_FILEMD5_H__

#include "entityx/entityx.h"

namespace WkCocos
{
	namespace Download
	{
		namespace Comp
		{

			struct LocalFile : entityx::Component<LocalFile> {
				LocalFile(std::string localpath)
				: m_path(localpath)
				{}
				
				std::string getPath()
				{
					return m_path;
				}
				
			private:

				std::string m_path; //local path of the file
			};

			struct LocalMD5 : entityx::Component<LocalMD5> {
				LocalMD5(std::string md5)
				: m_md5(md5)
				{}

				std::string getMD5()
				{
					return m_md5;
				}

			private:

				std::string m_md5; //md5 sig of local file
			};

			struct TempFile : entityx::Component<TempFile> {
				TempFile(std::string localpath)
				: m_path(localpath)
				{}

				std::string getPath()
				{
					return m_path;
				}

			private:

				std::string m_path; //local path of the temp file
			};

			struct TempMD5 : entityx::Component<TempMD5> {
				TempMD5(std::string md5)
				: m_md5(md5)
				{}

				std::string getMD5()
				{
					return m_md5;
				}

			private:

				std::string m_md5; //md5 sig of temp file
			};


			struct RemoteFile : entityx::Component<RemoteFile> {
				RemoteFile(std::string URL, std::string path)
				: m_url(URL)
				, m_path(path)
				{}

				std::string getURL()
				{
					return m_url;
				}

				std::string getPath()
				{
					return m_path;
				}

			private:

				std::string m_url; //URL of the remote file
				std::string m_path; //path of the remote file
			};

			struct RemoteMD5 : entityx::Component<RemoteMD5> {
				RemoteMD5(std::string md5)
				: m_md5(md5)
				{}

				std::string getMD5()
				{
					return m_md5;
				}

			private:

				std::string m_md5; //md5 sig of remote file
			};

		}//namespace Comp
	}//namespace Download
}//namespace WkCocos

#endif // __DFGAME_DOWNLOAD_ENTITY_COMP_FILEMD5_H__
