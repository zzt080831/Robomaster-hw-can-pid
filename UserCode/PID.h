#ifndef __PID_H
#define __PID_H

class PID{
	public:
		PID(float kp, float ki, float kd,float i_max, float out_max, float p_filter_k, float d_filter_k, float kfeedforward):kp_(kp),ki_(ki),kd_(kd),i_max_(i_max),out_max_(out_max),p_filter_k_(p_filter_k),d_filter_k_(d_filter_k),kfeedforward_(kfeedforward){
		}
		void reset();
		float calc(float ref,float fdb);
		float limit(float tar,float minimum,float maximum);
        float feedforward(float angle);
		
	private:
		float kp_ = 0;
		float ki_ = 0;
		float kd_ = 0;
		float i_max_ = 0;
		float out_max_ = 0;
		float d_filter_k_ = 1;
        float p_filter_k_ = 1;
		float last_err_ = 0;
		float err_sum_ = 0;
		float err_diff_ = 0;
		float err_ = 0;
        float kfeedforward_ = 0;
        float p_output_ = 0;
        float i_output_ = 0;
        float d_output_ = 0;
        float output_ = 0;
};

#endif