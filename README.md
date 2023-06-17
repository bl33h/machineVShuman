# machineVShuman
A multi-threaded simulation of production in a factory, specifically comparing the efficiency of production carried out by human workers versus production carried out by machines. Additionally, it generates a report for the user indicating whether it is a better option to invest more in human labor or acquire another machine.

<p align="center">
  <br>
  <img src="https://machinatorium.files.wordpress.com/2013/10/man-vs-machine.gif" alt="pic" width="500">
  <br>
</p>

<p align="center" >
  <a href="#general-information">General information</a> •
  <a href="#Files">Files</a> •
  <a href="#Features">Features</a> •
  <a href="#how-to-use">How To Use</a> 
</p>

## General information
- Application/Problem: Assessing the long-term efficiency and profitability of machine production compared to human labor.
- Context: The CEO of a company wants to determine whether it is more advantageous to hire a group of people for assembling parts per minute over a long period of time or to make a significant investment in purchasing a machine.
- Solution: Develop a program that simulates the productivity of both the machine and human workforce based on user-inputted data. The program analyzes and calculates the production time for each scenario using parallel programming techniques in different work processes. Ultimately, a report is generated, indicating the most viable option based on calculations and aligned with the company's conditions.
## Files

- src: the file that implements de solution.
- flowchart: the model construction.

## Features
The main features of the application include:
- Multi-threading: The code utilizes multi-threading to simulate concurrent production processes. It creates and manages threads for different production areas, allowing for parallel execution of tasks.
- User Input: The code prompts the user to input various information such as the type of work, wages, and investment in machines. This allows customization and flexibility in simulating different scenarios.
- Production Simulation: The code simulates the production process by coordinating the work of human workers and machines. It tracks the progress of production in different areas and ensures that the assembly process depends on the completion of a specific number of pieces in the previous area.
- Cost Calculation: The code calculates the production costs based on the number of assembled pieces and the wages of human workers. It provides insights into the financial aspects of production, helping users make informed decisions.
- Reporting: After simulating the production and calculating the costs, the code generates a report for the user. The report indicates whether it is more advantageous to invest in human labor or acquire another machine based on the simulated results. This feature assists users in making data-driven decisions for optimizing production efficiency and cost-effectiveness.
- Synchronization: The code employs synchronization mechanisms such as mutexes and conditions to ensure thread safety and proper coordination between human workers and machines during the production simulation.

## How To Use
To clone and run this application, you'll need [Git](https://git-scm.com) and a [C++ compiler](https://www.fdi.ucm.es/profesor/luis/fp/devtools/mingw.html) installed on your computer. From your command line:

...
```bash
# Clone this repository
$ git clone https://github.com/bl33h/machineVShuman

# Open the folder
$ cd src

# Run the app
$ g++ machineVShuman.cpp -o machineVShuman
$ ./machineVShuman
```
