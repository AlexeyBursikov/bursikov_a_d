#include "timer.h"

Stat::Stat() : count_(0), time_(0) { TimeLogger::instance().addStat(this); };

Stat::~Stat() {}
