#include "PID.h"
#include <math.h>
float PID::calc(float ref, float fdb){
	err_ = (ref-fdb)*p_filter_k_+last_err_*(1-p_filter_k_);
	err_diff_ = (err_ - last_err_)*d_filter_k_+err_diff_*(1-d_filter_k_);
	last_err_ = err_;
	err_sum_ = limit(err_sum_+err_,-i_max_,i_max_);
    p_output_ = err_*kp_;
    i_output_ = err_sum_*ki_;
    d_output_ = err_diff_*kd_;
    output_ = limit(err_*kp_+err_diff_*kd_+err_sum_*ki_,-out_max_,out_max_);
	return output_;
}
float PID::limit(float tar,float minimum,float maximum){
	if(tar>maximum) return maximum;
	if(tar<minimum) return minimum;
	return tar;
}
void PID::reset(){
	last_err_ = err_sum_ = err_diff_ = err_ = 0;
}
float PID::feedforward(float angle) {
    return kfeedforward_ * sin(angle*3.1415926/180.0);
}
