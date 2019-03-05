/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
namespace RobotMap {

namespace sensor {
    constexpr int DIOLaserSwitch = 5;
};

namespace Drive {

    namespace Left {
        constexpr int CANSparkNeo;
        constexpr int CANSparkCIM;
        constexpr int CANTalonCIM;
    };

    namespace Right {
        constexpr int CANSparkNeo;
        constexpr int CANSparkCIM;
        constexpr int CANTalonCIM;
    };

};

namespace Carriage {
    namespace Motor {
        constexpr int LeftWheel;
        constexpr int RightWheel;
    };
};

namespace Elevator {
    constexpr int ForwardNeo;
    constexpr int BackwardNeo;
    constexpr int SecondStageTalon;
};