#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();

 private:
    int prev_Total = 0;
    int prev_idle = 0;
};

#endif