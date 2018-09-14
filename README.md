# CarND_Project10MPC

Solution for Udacity Self driving car Nano degree tenth project: Model Predictive Control Project.

---

## Objective

Implement a Model Predictive controller controling a car traversing around a simulated track in Udacity simulator.

---

### Reflection

This project gives the oopertunity to try a different control schema than the PID controller tested during the previous project. The udacity simulator provides a simulated interactive car on a track, the controller should control the car motion around the track with no safety hazards it also need to deal with actuation delay of 100ms.

---

### Theory

Model predictive control is kind of an iterative control model. First the car process is modeled and then a cost function is defined.
An optimizer apply the cost function to the model and try to tune the control parameters (a/delta) to minimize the cost function value.

The Optimizer use the model to predict the car location for a given period at regular intervals defined during development, can be considered other hyper parameters.

#### The Model

The car model was derived during the classes it is as follows:

(1) x_t+1 = x_t + v_t * cos(psi_t) * dtx

(2) y_t+1 = y_t + v_t * sin(psi_t) * dty

(3) psi_t+1 = psi_t + (v_t/L_f) * delta * dtψ

(4) v_t+1 = v_t + a_t * dtv

(5) cte_t+1 = f(x_t) − y_t + (v_t * sin(eψ_t) dt)

(6) eψ_t+1 = psi_t - psi_dest + ((v_t/L_f) delta_t dt)

Equations (1), (2) and (4) are the normal equation of motion of any moving object.

Equation (3) represent the heading update based on our car model, The steering angle is multiplied by a factor represengint the "steerability" of our car. The factor is the vehicle velocity divided by the turn factor, as vehicle moves faster it is much more steerable, i.e. can go out of control easier :D, and the shorter our CG to the steering points, front wheels axle in our case, the tighetr the turns the car can make.

Equation (5) predicts the future cross track error it use the model to predict the future car position and it also accounts for any error due to wrong heading by adding the distance traveled due to a heading error.

Equation(6) predicts the future heading error.

####Timestep Length and Elapsed Duration (N & dt)

During classes we chose N = 25 and dt of 50 ms this gave us 1.25 seconds to predict, This time is good since no large scenery change is expected within less than 1 sec and any less would lead to underestimating the car position due to very small look ahead time.

However the 50 ms gap time is very low and wields nearly the same results of the previous points because the car didn't have enough time to move much actually.

I tested with multiple N and dt printing the state at each iteration but keeping the total time, i.e. N * dt, within 1.25 sec I settled on using N = 15 and dt = 85 ms.

####Polynomial Fitting and MPC Preprocessing

Unlike the quiz we had during class the points presented by the simulator are actual road points, i.e. the simulated road, and thus a third order polynomial at least is needed to fit the tight and loose turns present in it.

I made one transformation to relocate the origin point of the road points to the car origin point to ease the polynomial calculation.

####Model Predictive Control with Latency

The 100ms acctuation delay is acceptable since I am using a smaller time step 0.85ms and simulate for a sufficient time in the future 1.25sec.

---

Results
The car is able to traverse the whole track as requested, I have made a video with two laps shown to show that the MPC can handle the complete track at different speeds.
