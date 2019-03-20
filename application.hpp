/*
 * MtData application header driving the whole program
*/

#pragma once

namespace mtdata_prj {

/** @brief Run the MT project application
 *  @param const char* com_port
 *  @return none
 */
void Run(const char *com_port);


/** @brief Run the main MtData application thread
 *  @param const char* com_port
 *  @return none
 */
void MtDataAppThread(const char* com_port);

} // namespace mtdata_prj
