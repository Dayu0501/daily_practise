#pragma once

#include <sys/types.h>
#include <string>

#include "yt/log/logger.h"
#include "yt/util/mutex.h"

//! \namespace OssBase
namespace yt
{

	/*! \class DateFileLogger
	 * \brief �����ļ���־������
	 */
	class DateFileLogger : public Logger
	{
		public:

			/*! \brief ���캯��
			 * \param[in] szLogFile ��־�ļ�·�� ( �뾡��ʹ�þ���·�� )
			 */
			DateFileLogger(const std::string & sLogFile,const std::string & sLogFormat=/*Logger::*/DEFAULT_FORMAT,const std::string sTimeLimit = "");
			//DateFileLogger(const std::string & sLogFile, const std::string & sLogFormat=/*Logger::*/DEFAULT_FORMAT);
			virtual ~DateFileLogger();


			/*! \brief ʵ����Log��������sLogInfoд��ʱ���ļ�
			 * \param[in] iLogPriority ��־����
			 * \param[in] sLogMsg ��־��Ϣ
			 * \return 0:�ɹ� ��0:ʧ��
			 */
			virtual int Log(LogPriority iLogPriority,const std::string & sLogMsg);

		protected:

			//! \brief �õ���־�ļ���
			//! \return �����ڵ��ļ���
			std::string GetLogFileName();

		private:

			//! \brief ��־·��
			std::string sLogFile_;
			std::string sTimeLimit_;
			ThreadMutex mutex_;
			 
			int m_fd;
			struct tm cur_time;

	};

}
