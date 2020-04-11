#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void swap();
char get_block(void);
void print_slots(char slots[]);
unsigned int put_block(char block, unsigned int position, char array[]);
unsigned int remove_block(unsigned int position, char array[]);
unsigned int shift_right(unsigned int position);
unsigned int shift_left(unsigned int position);
bool robot_ltoreq_slot(char robot, char in_slot);
char switch_blocks(char robot, unsigned int position, char array[]);
bool test_empty(unsigned int position, char array[]);
char get_block_testone(void);
void recursiveShift(int i);
char get_block_testtwo(void);
char blockSwitcher();
void is_Done();
char get_block_testthree();
char get_block_testfour();
char get_block_testfive();
void specialRecursiveShift();
void specialMatchingThing();
char blockGetter();
bool equalP();

char blocks[20] = {' '};
char robot = ' ';
int index = 0;
int isDone = 0;
int runcounter = 0;
int flag = 0;
int tmpindex;
int switchCounter = 0;

// Change test case, can also be get_block();
char blockGetter() { return get_block_testone(); }

bool equalP(char robot, char block) {
  // Check if blocks are equal
  return (robot_ltoreq_slot(robot, block) && robot_ltoreq_slot(block, robot))
             ? true
             : false;
}
void is_Done() {
  tmpindex = index;
  while (index != 0) {
    index = (index > 0) ? shift_left(index) : shift_right(index);
  }
  for (; index < 20;) {
    if (test_empty(index, blocks)) {
      while (index != tmpindex) {
        index = (index > tmpindex) ? shift_left(index) : shift_right(index);
      }
      return;
    }
    index = shift_right(index);
  }
  isDone = 1;
  print_slots(blocks);
  cout << "Number of Swaps: " << switchCounter << endl;
}

int main() {
  while (isDone == 0) {
    is_Done();
    for (int i = 0; i < 200; i++) {
      swap();
    }
    isDone = 1;
    print_slots(blocks);
    cout << "Number of Swaps: " << switchCounter << endl;
  }
}

void swap() {
  is_Done();
  if (isDone == 1) {
    exit(1);
  }
  // If robot doesn't have a block, give him one
  if (robot == ' ' || robot == NULL) {
    robot = blockGetter();
  }
  // If 10th block is empty, take the block from the robot and put it in slot
  // 10, call swap();

  // cout << "Robot: " << robot << endl << "Index: " << index << endl;
  if (test_empty(9, blocks)) {
    while (index != 9) {
      index = (index > 9) ? shift_left(index) : shift_right(index);
    }
    robot = blockSwitcher();
    return;
  }
  // Check for outside array bounds
  if (index < 0) {
    //   cout << "Index less than 0" << endl;
    while (index != 0) {
      index = shift_right(index);
    }
    robot = blockSwitcher();
    index = shift_right(index);
    return;
  } else if (index > 19) {
    while (index != 19) {
      index = shift_left(index);
    }
    robot = blockSwitcher();
    return;
  }
  // Main sorter
  if (robot_ltoreq_slot(robot, blocks[index])) {
    // Equal
    if (equalP(robot, blocks[index])) {
      index = shift_left(index);
      robot = blockSwitcher();
      if (index == 0) {
        specialMatchingThing();
        robot = blockSwitcher();
        flag = 1;
      }
      if (robot_ltoreq_slot(robot, blocks[index])) {
        return;
      }
      index = shift_right(index);
      index = shift_right(index);
      while (index > 19) {
        index = shift_left(index);
      }
      if (test_empty(index, blocks)) {
        index = shift_left(index);
        if (equalP(robot, blocks[index])) {
          index = shift_right(index);
        }
      }

      // Less than
    } else {
      recursiveShift(0);
      return;
    }
    return;
    // Greater than
  } else {
    recursiveShift(1);
    return;
  }
  return;
}
void specialMatchingThing() {
  is_Done();
  if (isDone == 1) {
    exit(1);
  }
  if (index == 19) {
    return;
  }
  while (equalP(robot, blocks[index])) {
    index = shift_right(index);
    specialMatchingThing();
  }
}

void specialRecursiveShift() {
  if (test_empty(index, blocks)) {
    robot = blockSwitcher();
  }
  // If block is less than or equal, switch blocks, if greater, shift to right
  // and call again
  if (robot_ltoreq_slot(robot, blocks[index])) {
    robot = blockSwitcher();
  } else {
    index = shift_right(index);
    specialRecursiveShift();
  }
}

void recursiveShift(int i) {
  if (flag == 1) {
    robot = blockSwitcher();
    flag = 0;
    return;
  }

  if (i == 0) {

    if (equalP(robot, blocks[index]) && index == 0) {
      index = shift_right(index);
      if (robot_ltoreq_slot(robot, blocks[index])) {
        robot = blockSwitcher();
        specialRecursiveShift();
        return;
      }
      index = shift_left(index);
    }

    // If blocks[0] is filled, go forward until a greater block is found
    if (index == 0) {
      if (!test_empty(index, blocks)) {
        while (!robot_ltoreq_slot(robot, blocks[index])) {
          index = shift_right(index);
        }
        robot = blockSwitcher();

        return;
      }
    }
    // If robot block is less than array block, and array block is not a space
    if (robot_ltoreq_slot(robot, blocks[index]) && blocks[index] != ' ') {
      index = shift_left(index);
      recursiveShift(0);
    } else {
      robot = blockSwitcher();
      return;
    }
  } else {

    if (index == 19) {
      robot = blockSwitcher();
      return;
    }

    index = shift_right(index);
    if (equalP(robot, blocks[index])) {
      specialMatchingThing();
      robot = blockSwitcher();
      return;
    }

    index = shift_left(index);
    if (test_empty(index, blocks)) {
      index = shift_left(index);
      // If less than or equal to block on the left, place it one block to the
      // right
      if (robot_ltoreq_slot(robot, blocks[index])) {
        index = shift_right(index);
        robot = blockSwitcher();
        // If block on the left is greater, keep going until you reach a less or
        // equal
      } else {
        specialRecursiveShift();
      }
    }
    // If empty space after blocks that are in order, and held block is greater
    // than previous block
    index = shift_right(index);
    if (test_empty(index, blocks)) {
      index = shift_left(index);
      if (!robot_ltoreq_slot(robot, blocks[index])) {
        index = shift_right(index);
        robot = blockSwitcher();
        return;
      }
    }

    // If block after is less than held block
    if (robot_ltoreq_slot(robot, blocks[index])) {
      specialRecursiveShift();
    }
    index = shift_left(index);
    // If robot block is greater than array block, and array block is not a
    // space
    if (!robot_ltoreq_slot(robot, blocks[index]) && blocks[index] != ' ') {
      index = shift_right(index);
      recursiveShift(1);
    } else {
      robot = blockSwitcher();
    }
  }
}

char blockSwitcher() {
  if (index < 0) {
    return robot;
  }
  if (test_empty(index, blocks)) {
    put_block(robot, index, blocks);
    print_slots(blocks);
    return blockGetter();
  } else {
    switchCounter++;
    char b = switch_blocks(robot, index, blocks);
    print_slots(blocks);
    return b;
  }
}
// ------------------------------------------------------------------------ //
//																			//
//																			//
//				Functions for robot operations
////
//																			//
//																			//
// ------------------------------------------------------------------------ //

//
// Function get_block
// Reads in a single character value from the keyboard
// This is the input from the chute
// Returns: a single character in uppercase
//
// Example function call: 	block = get_block();

char get_block(void) {
  char block;
  cout << "Enter one block: ";
  cin >> block;
  return toupper(block);
}
//
// Function print_slots
// Prints the contents of the slots array in a well formatted form.
// Input: Array of slots
// Returns: Nothing (void)
//
// Example function call: print_slots(slot_array);

void print_slots(char slots[]) {
  unsigned int j = 1;
  for (j = 1; j <= 20; j++) {
    cout << setw(3) << j;
  }
  cout << endl;
  for (j = 0; j < 20; j++) {
    cout << setw(3) << slots[j];
  }
  cout << endl;
}
// Function put_block
// This function stores a character into the character array representing the
// slots
//
// Inputs:
// block - type char - The character to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// position - type unsigned int - the index of the slot where the block was
// placed
//
// Example function call: 	put_block(block, position, slots);

unsigned int put_block(char block, unsigned int position, char array[]) {
  bool debug = false;
  array[position] = block;
  if (debug)
    cout << "Block " << block << " inserted into slot " << position << endl;
  return position;
}

// Function remove_block
// This function removes a block from the slot array
// The slot where the block is removed is then set to a space
//
// Inputs:
// position - type unsigned int - index of the slot where block is located
// array - type char - array of slots containing the blocks
//
// Returns:
// block - type char - the block removed from the slot
//
// Example function call: 	remove_block(position, slots);

unsigned int remove_block(unsigned int position, char array[]) {
  bool debug = false;
  char block = ' ';
  block = array[position];
  array[position] = ' '; // Reset slot to blank after block removed
  if (debug)
    cout << "Block " << block << " removed from slot " << position + 1 << endl;
  return block;
}

// Function shift_right
// This function increments the index simulating a movement of the robot
// to the next higher slot (index) of the array
//
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position +
// 1
//
// Example function call:  position = shift_right(position)
//

unsigned int shift_right(unsigned int position) {
  bool debug = false;
  position++;
  if (debug)
    cout << "Position right shifted to " << position << endl;
  return position;
}

// Function shift_left
// This function decrements the index simulating a movement of the robot
// to the next lower slot (index) of the array
//
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position -
// 1
//
// Example function call: position = shift_left(position)
//

unsigned int shift_left(unsigned int position) {
  bool debug = false;
  position--;
  if (debug)
    cout << "Position left shifted to " << position << endl;
  return position;
}

// Function robot_ltoreq_slot
// This function compares the value of the block held by the robot
// with the value of the block in a slot
//
// Inputs:
// robot - type char - value of block held by robot
// in_slot - type char - value of block in the slot
//
// Returns:
// true or false
// TRUE if block held by robot is LESS than or equal to the block in slot
// FALSE if block held by robot is GREATER than block in slot
//
// Example function call: if ( compare_blocks(robot_block, slot_block) )
//
bool robot_ltoreq_slot(char robot, char in_slot) {
  bool debug = false;
  if (debug)
    cout << endl
         << "Comparing robot block " << robot << " with block in slot "
         << in_slot << endl;
  if (robot <= in_slot) {
    if (debug)
      cout
          << "Returning true. Robot block LESS than or EQUAL to block in slot. "
          << endl;
    return true;
  } else {
    if (debug)
      cout << "Returning false. Robot block GREATER than block in slot. "
           << endl;
    return false;
  }
}
// Function switch_blocks
// This function switches the block held by the robot with a block in a slot.
// After the switch the robot is holding the block removed from the slot.
//
// Inputs:
// robot - type char - The block to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// robot - type char. The value of the block removed from the slot.
//
// Example function call: block = switch_blocks(block,  position, array);
//

char switch_blocks(char robot, unsigned int position, char array[]) {
  char temp_hold;
  bool debug = false;
  if (debug)
    cout << "Switching blocks " << robot << " with " << array[position] << endl;
  temp_hold = robot;
  robot = array[position];
  array[position] = temp_hold;
  return robot;
}
// Function test_empty
// This function tests the array to determine if a slot is empty (NULL)
// or if the slot contains a blank. The slot array must be intialized to
// all NULL or all blanks (spaces) before any blocks are added.
//
// Inputs:
// position - type unsigned int - index of slot to be tested
//
// Returns:
// true or false as value o function
// TRUE if slot is empty
// FALSE if the slot contains a block
//
// Example function call: if ( test_empty(index, array) )
//
bool test_empty(unsigned int position, char array[]) {
  char blank = ' '; // Blank space
  bool debug = false;
  if (array[position] == NULL || array[position] == blank) {
    if (debug)
      cout << "Slot " << position << " empty. " << endl;
    return true;
  } else {
    if (debug)
      cout << "Slot " << position << " contains a block " << endl;
    return false;
  }
}

// ------------------------------------------------------------------------ //
//																			//
//																			//
//				Functions for robot test cases
////
//																			//
//																			//
// ------------------------------------------------------------------------ //

//
// Function get_block_testcase
// Returns blocks for a given test case one at a time
// This function can be used for all five test cases.
//
// Input: Unsigned int case designating test case 1-5.
// Input: Index of letter desired 0 - 19.
// Returns: a single uppercase character
//
// Example function call: 	block = get_block_testcase(1, 0);
// Returns first letter of test case 1.

char get_block_testcase(unsigned int testcase, unsigned int index) {
  string testcases[5] = {"AXFIUTRPQVWSEYJINYTB", "ABFGHIJKMOPRSTUVWXYZ",
                         "ZYXWVUTSRPOKJIIHGFBA", "AAAAAYYYYYQQQQQXXXXX",
                         "XXXAAAZZZAAYYVVVVQQQ"};

  return testcases[testcase - 1].at(index);
}

//
// Function get_block_testone
// Returns blocks for test case one one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testone();

char get_block_testone(void) {
  static unsigned int index = 0;
  char test_case_one[21] = "AXFIUTRPQVWSEYJINYTB";
  return test_case_one[index++];
}

//
// Function get_block_testtwo
// Returns blocks for test case two one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testtwo();

char get_block_testtwo(void) {
  static unsigned int index = 0;
  char test_case_two[21] = "ABFGHIJKMOPRSTUVWXYZ";
  if (index < 21) {
    return test_case_two[index++];
  }
}

//
// Function get_block_testthree
// Returns blocks for test case three one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testthree();

char get_block_testthree(void) {
  static unsigned int index = 0;
  char test_case_three[21] = "ZYXWVUTSRPOKJIIHGFBA";
  if (index < 21) {
    return test_case_three[index++];
  }
}
//
// Function get_block_testfour
// Returns blocks for test case four one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testfour();

char get_block_testfour(void) {
  static unsigned int index = 0;
  char test_case_four[21] = "AAAAAYYYYYQQQQQXXXXX";
  return test_case_four[index++];
}

//
// Function get_block_testfive
// Returns blocks for test case five one at a time
// Returns: a single character
//
// Example function call: 	block = get_block_testfive();

char get_block_testfive(void) {
  static unsigned int index = 0;
  char test_case_five[21] = "XXXAAAZZZAAYYVVVVQQQ";
  return test_case_five[index++];
}
