# List
 - Cargo Intake Lock
 - Carriage Cargo Auto-Lock \0\0\0\0\0\0\0   done
 - Elevator Floor Lock
 - Streaming Boardcast      \0\0\0\0\0\0   Need Test
 - RobotMap Update & Reframe  \0\0\0\0\0\0\0\0 Done & Wait Test

# RobotMap (test)
Try to define all the port numbers for controllors & sensors in RobotMap.h 

Make the code easier to acess and maintain 

[CST 2019/03/05 Tue. 16:23]

# key blinding

## Drive:
| Functionality             | Pilot    | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| Drive (Arcade)            | Pilot    | Main Axis | Axis             |
| Switch Mode (Low / High)  | Pilot    | Button 2  | Press            |

## Cargo Intake:

| Functionality             | Pilot    | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| Up                        | Pilot    | Button 7  | Hold             |
| Down                      | Pilot    | Button 8  | Hold             |
| takein                    | Pilot    | trigger   | Hold             |
| takein Speed Controller   | Pilot    | Throttle  | Axis             |

## Hatch Intake
| Functionality             | Pilot    | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| Hatch IN / OUT            | Co Pilot | Button 2  | Press            |
| Panel Lock                | Co Pilot | Button 3  | Press            |
| Panel UnlocK              | Co Pilot | Button 4  | Press            |

## Elevator
| Functionality             | Pilot    | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| Level - Ground            | Co Pilot |           | Press            |
| level - Mid               | Co Pilot |           | Press            |
| level - Top               | Co Pilot |           | Press            |
| Up / Down                 | Co Pilot | POV  /5 / 10     | Axis             |

## Carriage
| Functionality             | Pilot  p  | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| take-in                   | Pilot    | trigger   | Press            |
| take-in Speed Controller  | Pilot    | Throttle  | Axis             |
| Shoot                     | Co Pilot | trigger   | Press/Hole       |