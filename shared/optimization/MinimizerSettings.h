#ifndef __MINIMIZER_SETTINGS_H__
#define __MINIMIZER_SETTINGS_H__

class MinimizerSettings{

public:

  int iterationAmount = 10;
  double priorSize = 1;

  int convergenceFactor = 1000;
  double projectedGradientTolerance = 0.001;
  int maxFunctionEvals = 50;

};

#endif
