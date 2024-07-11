#include <frui_hal.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LEN 20 // Adjust as needed

char random_char(char type) {
  int random_value = rand();
  switch (type) {
    case 'l': // lowercase letter
      return (char)(random_value % 26 + 'a');
    case 'u': // uppercase letter
      return (char)(random_value % 26 + 'A');
    case 'd': // digit
      return (char)(random_value % 10 + '0');
    case 's': // special symbol
      // Modify this range based on your desired symbols
      return (char)(random_value % 74 + 33); // printable symbols from ! to ~
    default:
      return ' '; // Handle invalid type
  }
}

void generate_password(char* password, int length, char complexity) {
  int i;
  int char_types = 0;

  // Enforce at least one character from each type if complexity is high
  if (complexity == 'h') {
    char_types = 4;
  }

  // Generate password with desired complexity
  for (i = 0; i < length; i++) {
    char type;
    do {
      type = random_char('l' + rand() % 4); // Choose random character type
    } while (complexity == 'h' && char_types < 4 && !(strchr("luds", type)));
    password[i] = type;
    if (complexity == 'h' && strchr("luds", type)) {
      char_types++;
    }
  }

  password[length] = '\0'; // Terminate the string
}

int main(void) {
  char password[MAX_PASSWORD_LEN + 1];
  int length, complexity;

  frui_draw_text(0, 0, "Password Length (1-20):");
  length = frui_input_int(0, 21);
  if (length < 1 || length > MAX_PASSWORD_LEN) {
    frui_draw_text(0, 10, "Invalid length!");
    return 1;
  }

  frui_draw_text(0, 20, "Complexity (l: low, h: high):");
  complexity = frui_read_char(0, 31);
  if (complexity != 'l' && complexity != 'h') {
    frui_draw_text(0, 30, "Invalid complexity!");
    return 1;
  }

  generate_password(password, length, complexity);
  frui_draw_text(0, 40, "Your Password:");
  frui_draw_text(0, 50, password);

  frui_draw_text(0, 60, "Press any button to exit.");
  frui_wait_for_button_press(NULL);

  return 0;
}
