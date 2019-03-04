#include "mav_active_3d_planning/trajectory_evaluator.h"
#include "mav_active_3d_planning/module_factory.h"

#include <ros/param.h>

namespace mav_active_3d_planning {
    namespace value_computers {

        // Linear combination of cost and gain
        class LinearValue : public ValueComputer {
            friend ModuleFactory;

        public:
            LinearValue(double cost_weight, double gain_weight)
                : cost_weight_(cost_weight),
                  gain_weight_(gain_weight) {}

            bool computeValue(TrajectorySegment *traj_in) {
                traj_in->value = gain_weight_ * traj_in->gain - cost_weight_ * traj_in->cost;
                return true;
            }

        protected:
            LinearValue() {}

            void setupFromParamMap(ParamMap *param_map){
                setParam<double>(param_map, "cost_weight", &cost_weight_, 1.0);
                setParam<double>(param_map, "gain_weight", &gain_weight_, 1.0);
            }

            double cost_weight_;
            double gain_weight_;
        };

        // This module is replaced in next version

    } // namespace value_computers
} // namepsace mav_active_3d_planning
