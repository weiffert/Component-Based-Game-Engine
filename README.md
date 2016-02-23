# Component-Based-Game-Engine
This is a game engine designed to use entities and component based design.
An implementation project will be missile command.

What it is:
A component-based game engine is based off of using properties to define an entity and controllers to control the entity. 

Some Definitions:
Entity: a class that holds properties and controllers. 
Property: defines what an entity is, how it behaves, and others.
Controller: makes the entity behave in a particular manner based on the properties the entity has.
Game State: holds the entities for the current state and defines how the game updates.

How it works:
Properties, entities, controllers, and states are held by pointer handles in the SystemManager class. This allows multiple entities to have the same properties and controllers, and have multiple states have the same entities. Additionally, almost everything is passed by pointer references so that the game runs smoother, for data is not being copied, edited, and destroyed.

Game Flow:
1. The executable is launched.
2. Main logs the time to a file.
3. Reads data from a file.
4. Creates a game.
5. Runs the game.
6. Game creates necessary classes and starts the game loop.
7. Game starts with creating properties, entities, controllers, and states in that order with as much information coming from files as possible. These are stored in SystemManager.
8. Properties contain data. If it is an image, texture, or sound, then it gets the data from the AssetManager.
9. Entities contain properties and controllers.
10. States contain entities.
11. All of this data is gotten from the SystemManager.
12. Game then moves to the next state and shows a welcome screen.
13. Game then shows a menu.
14. If play is selected, then the state moves to the level state and game play begins.
15. If escape is pressed, show the pause state.
16. If quit is selected, go to the menu.
17. If return is selected, go back to the game state.
18. If the game is done, show the kill screen.
19. Reinitialize the game level states.
20. Otherwise, continue.
21. Else, quit the game.

Editing:
Any new file that is added needs to be in the project folder. Its filename needs to be included into "file.txt". The substrings should NOT BE EDITED! No like class types should have the same id(in the case of everything) or number(in the case of states). This will make bad things happen! 

Edit properties: Create a new .txt with "property" (Without quotations) in the filename or open an existing one. Please be descriptive NO SPACES IN THE FILE NAME. Follow the format of:

id ;
type ;
value value ;

There should only be one line of values. If there is one, do "value ;" There should ALWAYS be a default value! If there are two or more, do "value value value ;" Have a space between values. 
Type should be the name of the data type EXACTLY! C++ is case-sensitive. ALWAYS check the source code that the data type is currently used in the switch statements in StateLoading and StatePause. Also, check if data type switching is available for the data type.

Edit entities: Create a new .txt with "entity" (Without quotations) in the filename or open an existing one. Please be descriptive NO SPACES IN THE FILE NAME. Follow the format of:

id ;
propertyId ;
propertyId value value ;

Entites can have multiple properties. Using just the propertyId links the entity to the property with the default values. If other values are included, the entity takes in a copy of the same property and changes the values accordingly.

Edit controllers: Two options: Edit an existing one or create a new controller.
1. open the .cpp and .h file for the controller or edit the .txt file for the id and required properties. Edit accordingly.
2. Just define a new .cpp and .h, write the constructor, destructor, and control function, and then link it to the proper game files. Then, create a new .txt file with "controller" in the name and no spaces. Follow the format of:

id ;
propertyId ;
propertyId ;

PropertyId defines the properties that are required. 
Then, you can use the new controller.

Edit states: States only have an id and an identification number. The only way to edit what is in a state is to change entity properties with the id of "state", for this is what defines what is in a state. Follow the format of:

id ;
number ;

This creates a new state. The number should be related to its position in game flow. For instance, level one goes before level two, but the main menu goes before all of that. There should only be one loading state! This will make duplicates of all of the entities, properties, controllers, and states everytime a new state is used! This tumbles the program into an INFINITE LOOP!!! Don't do it. 
