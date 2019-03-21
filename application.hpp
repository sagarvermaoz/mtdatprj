/*
 * MtData application header driving the whole application
 */

#pragma once

namespace mtdata_prj {
/**
 * @class Application
 * Main application class for MtdataApp
 */
class Application {
public:
  /** @brief Run the MT project application
   *  @param const char* com_port
   *  @return none
   */
  static void Run(const char *com_port);

  /** @brief Run the main MtData application thread
   *  @param const char* com_port
   *  @return none
   */
  static void MtDataAppThread(const char *com_port);
};

} // namespace mtdata_prj
