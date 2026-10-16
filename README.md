building a software in the loop physics simulator for an Adaptive Cruise Control system that can be used in vehicles

to edit the simulation as you wish, you need to dive into the main.c until i build the customizable mission planner

To run the project you will need to run:

mkdir build && mkdir output && touch output/vehicle_status.csv && cd build && cmake .. && make && ./acc_sim && cd ..

python -m venv venv && source venv/bin/activate && pip install -r requirements.txt && python visualisation.py
