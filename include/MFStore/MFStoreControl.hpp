// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB MFStore Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  MFStoreControl.hpp

   File Description  :  Include file for the MFStoreControl class.

   Revision History  :  2021-02-14 --- Creation.
                           Michael L. Brock

      Copyright Michael L. Brock 2021 - 2024.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__MFStore__MFStoreControl_hpp__HH

#define HH__MLB__MFStore__MFStoreControl_hpp__HH 1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file MFStoreControl.hpp

   \brief   Include file for the MFStoreControl class.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <MFStore/MFStore.hpp>

#ifdef _Windows
# pragma warning(push)
# pragma warning(disable:4061 4365)
#endif // #ifdef _Windows

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#ifdef _Windows
# pragma warning(pop)
#endif // #ifdef _Windows

#include <memory>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace MFStore {

// ////////////////////////////////////////////////////////////////////////////
#ifndef _MSC_VER
typedef int    MFStoreFileHandle;
#else
typedef HANDLE MFStoreFileHandle;
#endif // #ifndef _MSC_VER
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
using FileMapping      = boost::interprocess::file_mapping;
using MappedRegion     = boost::interprocess::mapped_region;
using FileMappingSPtr  = std::shared_ptr<FileMapping>;
using MappedRegionSPtr = std::shared_ptr<MappedRegion>;
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
class MFStoreControl
{
public:
	MFStoreControl();
	MFStoreControl(const std::string &file_name, MFStoreLen file_size,
		MFStoreLen mmap_size, MFStoreLen alloc_gran);
/*
   CODE NOTE: Pending review
	MFStoreControl(FileMappingSPtr mapping_sptr, MappedRegionSPtr region_sptr);
*/

	bool               IsActive() const;
	bool               CheckIsActive() const;
	const std::string &GetFileName() const;
	MFStoreFileHandle  GetFileHandle() const;
	MFStoreLen         GetFileSize() const;
	MFStoreLen         GetMmapSize() const;
	MFStoreLen         GetAllocGran() const;
	const void        *GetMmapAddress() const;
	FileMappingSPtr    GetMappingSPtr() const;
	MappedRegionSPtr   GetRegionSPtr() const;

private:
	FileMappingSPtr  mapping_sptr_;
	MappedRegionSPtr region_sptr_;
	std::string      file_name_;
	MFStoreLen       file_size_;
	MFStoreLen       mmap_size_;
	MFStoreLen       alloc_gran_;
};
// ////////////////////////////////////////////////////////////////////////////

} // namespace MFStore

} // namespace MLB

#endif // #ifndef HH__MLB__MFStore__MFStoreControl_hpp__HH

