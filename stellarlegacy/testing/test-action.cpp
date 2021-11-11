#include "gamelogic/fleetaction.h"
#include "admin/parser-use.h"
#include <cstdio>



bool TestActionClass()
{
  // load the action-test.sl file
  FILE* f;

  if ( !(f = fopen("testing/test-action.sl", "r")) ) {
    cerr << "Failed to open file!!" << endl;
    exit(-1);
  }

  //  TActionSequencer Sequencer;

  //  parserSequencer = &Sequencer;

  //  yyrestart(f);

  //  yyparse();

  //  fclose(f);

  // update pending links
  if ( TLinkUpdate::instance()->checkConsistency() == false )  {
    cerr << "action test: failed consistency check at end of load" << endl;
    return false;
  }

  // mark end of exec flow for this player
  //  Sequencer.AddExecutionFlowBlock();

  // execute player orders - will delete the involved actions
  //  Sequencer.RunSequence();

  // create movement orders
  //  Sequencer.Restart();

  // foreach fleet (all fleets)
  //   create action "movement" for fleet

  //  Sequencer.RunSequence();

  return false;
}
