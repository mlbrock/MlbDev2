// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// MLB Utility Library Include File
// ////////////////////////////////////////////////////////////////////////////
/*
   File Name         :  GetEnvironment.hpp

   Revision History  :  1993-10-02 --- Creation
                           Michael L. Brock
                        2023-01-09 --- Migration to C++ MlbDev2/Utility.
                           Michael L. Brock

      Copyright Michael L. Brock 1993 - 2023.
      Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
      http://www.boost.org/LICENSE_1_0.txt)

*/
// ////////////////////////////////////////////////////////////////////////////

#ifndef HH__MLB__Utility__GetEnvironment_hpp__HH

#define HH__MLB__Utility__GetEnvironment_hpp__HH   1

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
/**
   \file GetEnvironment.hpp

   \brief   The MLB environment variable support header file.
*/
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
// Required include files...
// ////////////////////////////////////////////////////////////////////////////

#include <Utility/EnvElement.hpp>

// ////////////////////////////////////////////////////////////////////////////

namespace MLB {

namespace Utility {

// ////////////////////////////////////////////////////////////////////////////
API_UTILITY void           GetEnvironment(EnvpList &env_list);
API_UTILITY EnvpList       GetEnvironment();

API_UTILITY void           EnvpListToEnvElementList(const EnvpList &envp_list,
	EnvElementList &env_element_list);
API_UTILITY EnvElementList EnvpListToEnvElementList(
	const EnvpList &envp_list = GetEnvironment());
API_UTILITY void           EnvElementListToEnvpList(
	const EnvElementList &env_element_list, EnvpList &envp_list);
API_UTILITY EnvpList       EnvElementListToEnvpList(
	const EnvElementList &env_element_list);

API_UTILITY void           EnvpListToEnvElementSet(const EnvpList &envp_list,
	EnvElementSet &env_element_list);
API_UTILITY EnvElementSet  EnvpListToEnvElementSet(const EnvpList &envp_list);
API_UTILITY void           EnvElementSetToEnvpList(
	const EnvElementSet &env_element_list, EnvpList &envp_list);
API_UTILITY EnvpList       EnvElementSetToEnvpList(
	const EnvElementSet &env_element_list);

API_UTILITY void           MergeEnvironment(const EnvpList &base_env,
	const EnvpList &added_env, EnvpList &result_env,
	bool merge_smart_flag = false, bool merge_path_flag = false);
API_UTILITY EnvpList       MergeEnvironment(const EnvpList &override_env,
	const EnvpList &added_env = GetEnvironment(), bool merge_smart_flag = false,
	bool merge_path_flag = false);

API_UTILITY void           CheckEnvironment(
	const EnvpList &envp_list = GetEnvironment());
// ////////////////////////////////////////////////////////////////////////////

} // namespace Utility

} // namespace MLB

#endif // #ifndef HH__MLB__Utility__GetEnvironment_hpp__HH

