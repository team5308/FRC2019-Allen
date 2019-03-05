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
| Switch Mode (Low / High)  | Pilot    | Button 1  | Press            |

## Cargo Intake:

| Functionality             | Pilot    | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| Up                        | Pilot    | Button 11 | Hold             |
| Down                      | Pilot    | Button 12 | Hold             |
| takein                    | Pilot    | trigger   | Hold             |
| takein Speed Controller   | Pilot    | Throttle  | Axis             |

## Hatch Intake
| Functionality             | Pilot    | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| Panel Lock / Unlock       | Co Pilot |           | Press            |
| Hatch Out                 | Co Pilot | Button 3  | Press            |
| Hatch In                  | Co Pilot | Button 4  | Press            |

## Elevator

| Functionality             | Pilot    | Key       | Operation Method |
|---------------------------|----------|-----------|------------------|
| Level - Ground            | Co Pilot |           | Press            |
| level - Mid               | Co Pilot |           | Press            |
| level - Top               | Co Pilot |           | Press            |
| Up / Down                 | Co Pilot | Main Axis | Axis             |
