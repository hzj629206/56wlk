/***************************************************************************
 * 
 * 
 **************************************************************************/
 
 
 
/**
 * @file bsl_binarchive.h
 * @brief 
 *  
 **/


#ifndef  __BSL_BINARCHIVE_H_
#define  __BSL_BINARCHIVE_H_

#include <bsl/utils/bsl_debug.h>
#include <stdlib.h>
#include <string.h>
#include <bsl/archive/bsl_stream.h>

namespace bsl
{
class binarchive
{
protected:
	bsl::stream &_fd;
public:
	binarchive(bsl::stream & fd) : _fd(fd) {}
	~binarchive() {}
		
	/**
	 * @brief ��bsl stream ���ж�ȡһ��ʵ������
	 *
	 * @param [out] tp   : _Tp* ��NULLָ��
	 * @return  int �ɹ�����0,����ʧ��
	 * @retval  tp��NULL ��core
	 * @see 
	 * @note 
	**/
	template <typename _Tp>
	int read(_Tp *tp) {
		_fd.start_trans();
		int ret = bsl::deserialization(*this, *tp);
		if (ret == 0) {
			_fd.comit_trans();
		} else {
			_fd.drop_trans(false);
		}
		return ret;
	}

	/**
	 * @brief ��stream����������
	 *
	 * @param [in] tp   : const _Tp& ��Ҫд���ʵ������
	 * @return int  �ɹ�����0,����ʧ��
	 * @retval   
	 * @see 
	 * @note 
	**/
	template <typename _Tp>
	int write(const _Tp & tp) {
		_fd.start_trans();
		int ret = bsl::serialization(*this, tp);
		if (ret == 0) {
			ret = _fd.comit_trans();
			if (ret != 0) {
				_fd.drop_trans(true);
			}
		} else {
			_fd.drop_trans(true);
		}
		return ret;
	}

public:
	/**
	 * @brief ��stream����д��size�������
	 *
	 * @param [in/out] dat   : const void*
	 * @param [in/out] size   : size_t
	 * @return 0 ��ʾ�ɹ�
	 * @retval   
	 * @see 
	 * @note 
	**/
	int push(const void *dat, size_t size) {
		//��������õײ�ȥ��
		return _fd.write(dat, size);
	}

	/**
	 * @brief ��stream���������
	 *
	 * @param [in/out] dat   : void*
	 * @param [in/out] size   : size_t
	 * @return  int 0��ʾ�ɹ�,����ʧ��
	 * @retval   
	 * @see 
	 * @note 
	**/
	int pop(void *dat, size_t size) {
		return _fd.read(dat, size);
	}
};

}
#endif  //__BSL_BINARCHIVE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */