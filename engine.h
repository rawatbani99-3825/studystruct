#ifndef ENGINE_H
#define ENGINE_H

#include "analysis.h"

class StudyPlannerEngine {
    Analysis analysis;
public:
    bool run();   // shows the menu; true = user logged out, false = user chose Exit
};

#endif
