#include "hangman_helpers.h"

#include <assert.h>

int main(void) {
  assert(string_contains_character("Hello", 'H'));
  assert(!string_contains_character("Hello", 'h'));
  assert(!string_contains_character("Hello", 'z'));

  assert(read_letter() == 'a');

  assert(is_lowercase_letter(read_letter()));
  assert(validate_secret("abc"));
  assert(validate_secret("a"));
  assert(!validate_secret("A"));
  assert(validate_secret("a 'b-c"));
  assert(!validate_secret("abBc"));
  assert(!validate_secret("abc1"));
  assert(!validate_secret("~abc"));
  assert(validate_secret(
      "lrnorrswefjvkkzyuwrjcuoaunkzsfliccypmbxzxvdibttgdrpsappgbbfqdkxjcsvpesjw"
      "ukxjltpsfnehunjlrqnzsorrwnhccnlbkzickvphupndghcstvcqtasbkkhbtnjzvilxejbt"
      "sogyikuwgctzilmhcbuargtgmrrczqvjeluayjldfnpwykiwjkszwiliailbltwqjwzslzuc"
      "hxczpctcpmlqpfspgbddfnciptibytslbxdpcpef"));
  assert(!validate_secret(
      "lrnorrswefjvkkzyuwrjcuoaunkzsfliccypmbxzxvdibttgdrpsappgbbfqdkxjcsvpesjw"
      "ukxjltpsfnehunjlrqnzsorrwnhccnlbkzickvphupndghcstvcqtasbkkhbtnjzvilxejbt"
      "sogyikuwgctzilmhcbuargtgmrrczqvjeluayjldfnpwykiwjkszwiliailbltwqjwzslzuc"
      "hxczpctcpmlqpfspgbddfnciptibytslbxdpcpeflrnorrswefjvkkzyuwrjcuoaunkzsfli"
      "ccypmbxzxvdibttgdrpsappgbbfqdkxjcsvpesjwukxjltpsfnehunjlrqnzsorrwnhccnlb"
      "kzickvphupndghcstvcqtasbkkhbtnjzvilxejbtsogyikuwgctzilmhcbuargtgmrrczqvj"
      "eluayjldfnpwykiwjkszwiliailbltwqjwzslzuchxczpctcpmlqpfspgbddfnciptibytsl"
      "bxdpcpef"));
}
