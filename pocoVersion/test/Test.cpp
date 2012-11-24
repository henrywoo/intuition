#include <iostream>
#include "../utils.h"
#include "Test.h"

using namespace std;


int Test::runModule(string moduleName, vector<string> args) {
  int rc(0);
  try
  {
    Poco::Pipe outPipe;
    Poco::ProcessHandle ph = Poco::Process::launch(moduleName, args, 0, &outPipe, 0);
    Poco::PipeInputStream istr(outPipe);
    Poco::StreamCopier::copyStream(istr, std::cout);
    rc = ph.wait();
    logger().information(Poco::format("  return code = %d", rc));
  }
  catch (Poco::SystemException& exc)
  {
    logger().warning(exc.displayText());
  }
  return rc;
}

int Test::main(const vector<string>& args) {
#ifdef DEBUG
  logger().information("Debug mode activated");
#endif
#ifdef OS_LINUX
  logger().information("Opearting system: Linux");
#endif

  if ( !_helpRequested ) {
    // Read config from properti file:
    //  db config (position)
    //  pyClass
    //  RScript
    // Handling a json order
    string command = "{\"name\": \"google\", \"days\": 2, \"deps\": false}";
    quantrade::DataSubsystem& database = getSubsystem<quantrade::DataSubsystem>();
    logger().information("Connected to database: " + toStr(database.name()));
    database.test();

    // Dependancies won't be handle at this time
    
    // Download (data submodule)

    // Compute (compute submodule)
  }
  return Application::EXIT_OK;
}
