#include "mathlib.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define EPSILON 1e-14

void test_stack(void) {
  printf("=== STACK TESTS ===\n");

  double item = 0;

  // Peek empty stack
  printf("Peeking empty stack: ");
  assert(!stack_peek(&item)); // Should fail (empty)
  printf("PASS\n");

  // Push items
  for (int i = 0; i < STACK_CAPACITY; i++) {
    assert(stack_push(i));
  }
  assert(stack_size == STACK_CAPACITY);
  printf("Push 64 items: PASS\n");

  // Peek top
  assert(stack_peek(&item));
  assert(item == STACK_CAPACITY - 1);
  printf("Peek top item: PASS\n");

  // Pop 3 items
  for (int i = STACK_CAPACITY - 1; i > STACK_CAPACITY - 4; i--) {
    assert(stack_pop(&item));
    assert(item == i);
  }
  printf("Pop 3 items: PASS\n");

  stack_clear();
  assert(stack_size == 0);
  printf("Clear stack: PASS\n\n");
}

void test_operators(void) {
  printf("=== OPERATOR TESTS ===\n");

  double item = 0;

  // Prepare stack
  for (int i = 0; i < 64; i++)
    assert(stack_push(i));

  // Unary operators
  assert(apply_unary_operator(my_unary_operators['s']));
  stack_pop(&item);
  printf("Sin(63) = %.10f\n", item);

  assert(apply_unary_operator(my_unary_operators['c']));
  stack_pop(&item);
  printf("Cos(62) = %.10f\n", item);

  assert(apply_unary_operator(my_unary_operators['t']));
  stack_pop(&item);
  printf("Tan(61) = %.10f\n", item);

  assert(apply_unary_operator(my_unary_operators['a']));
  stack_pop(&item);
  printf("Fabs(60) = %.10f\n", item);

  assert(apply_unary_operator(my_unary_operators['r']));
  stack_pop(&item);
  printf("Sqrt(59) = %.10f\n", item);

  // Binary operators
  assert(apply_binary_operator(binary_operators['+']));
  stack_pop(&item);
  printf("58 + 57 = %.10f\n", item);

  assert(apply_binary_operator(binary_operators['-']));
  stack_pop(&item);
  printf("56 - 55 = %.10f\n", item);

  assert(apply_binary_operator(binary_operators['*']));
  stack_pop(&item);
  printf("54 * 53 = %.10f\n", item);

  assert(apply_binary_operator(binary_operators['/']));
  stack_pop(&item);
  printf("52 / 51 = %.10f\n", item);

  printf("\n");
}

void test_mathlib(void) {
  printf("=== MATHLIB TESTS ===\n");

  double inputs[] = {-1, 0, 1};
  printf("\nABS TESTS\n");
  printf("%-10s %-15s %-15s\n", "Input", "Abs(x)", "Expected");
  printf("-----------------------------------\n");
  for (int i = 0; i < 3; i++) {
    double result = Abs(inputs[i]);
    printf("%-10.2f %-15.10f %-15.10f\n", inputs[i], result, fabs(inputs[i]));
    assert(result == fabs(inputs[i]));
  }

  double sqrt_inputs[] = {-1, 0, 9};
  printf("\nSQRT TESTS\n");
  printf("%-10s %-15s %-15s\n", "Input", "Sqrt(x)", "Expected");
  printf("-----------------------------------\n");
  for (int i = 0; i < 3; i++) {
    double result = Sqrt(sqrt_inputs[i]);
    if (sqrt_inputs[i] < 0) {
      printf("%-10.2f %-15s %-15s\n", sqrt_inputs[i], "NaN", "NaN");
      assert(result != result); // NaN check
    } else {
      printf("%-10.2f %-15.10f %-15.10f\n", sqrt_inputs[i], result,
             sqrt(sqrt_inputs[i]));
      assert(fabs(result - sqrt(sqrt_inputs[i])) < EPSILON);
    }
  }

  double trig_inputs[] = {0, 1, PI / 4, PI / 2, PI, 3 * PI / 2, 7 * PI / 4};
  printf("\nTRIG TESTS\n");
  printf("%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", "x", "Sin(x)", "sin(x)",
         "Cos(x)", "cos(x)", "Tan(x)", "tan(x)");
  printf("---------------------------------------------------------------------"
         "-----------------------------------------------------\n");

  for (size_t i = 0; i < sizeof(trig_inputs) / sizeof(trig_inputs[0]); i++) {
    double x = trig_inputs[i];
    double my_sin = Sin(x), std_sin = sin(x);
    double my_cos = Cos(x), std_cos = cos(x);
    double my_tan = Tan(x), std_tan = tan(x);

    printf("%-15.10f %-15.10f %-15.10f %-15.10f %-15.10f", x, my_sin, std_sin,
           my_cos, std_cos);

    if (fabs(std_cos) < EPSILON) {
      printf(" %-15s %-15s\n", "undefined", "undefined");
    } else {
      printf(" %-15.10f %-15.10f\n", my_tan, std_tan);
    }

    assert(fabs(my_sin - std_sin) < EPSILON);
    assert(fabs(my_cos - std_cos) < EPSILON);
    if (fabs(std_cos) >= EPSILON)
      assert(fabs(my_tan - std_tan) < EPSILON);
  }
}

void test_invalid_inputs(void) {
  printf("\n=== INVALID INPUT TESTS ===\n");

  double item = 0;

  /* ---------- STACK UNDERFLOW ---------- */
  stack_clear();
  assert(stack_size == 0);

  assert(!stack_pop(&item));  // can't pop empty
  assert(!stack_peek(&item)); // can't peek empty

  printf("Stack underflow tests passed\n");

  /* ---------- STACK OVERFLOW ---------- */
  stack_clear();

  for (int i = 0; i < STACK_CAPACITY; i++) {
    assert(stack_push(i));
  }

  assert(!stack_push(999)); // pushing past capacity must fail
  printf("Stack overflow test passed\n");

  /* ---------- UNARY OPERATOR WITH EMPTY STACK ---------- */
  stack_clear();

  assert(!apply_unary_operator(my_unary_operators['s']));
  assert(!apply_unary_operator(my_unary_operators['c']));

  printf("Unary operator empty-stack tests passed\n");

  /* ---------- BINARY OPERATOR WITH TOO FEW OPERANDS ---------- */
  stack_clear();
  stack_push(1);

  assert(!apply_binary_operator(binary_operators['+']));
  assert(!apply_binary_operator(binary_operators['-']));

  printf("Binary operator insufficient operand tests passed\n");

  /* ---------- DIVISION BY ZERO ---------- */
  stack_clear();
  stack_push(5);
  stack_push(0);

  bool ok = apply_binary_operator(binary_operators['/']);

  /* Depending on your implementation:
     - either operator_div returns false
     - or it returns true and pushes +/-inf
  */

  if (!ok) {
    printf("Division by zero correctly rejected\n");
  } else {
    stack_peek(&item);
    printf("Division by zero result: %f\n", item);
  }

  stack_clear();

  /* ---------- INVALID PARSE INPUT ---------- */
  assert(!parse_double("abc", &item));
  assert(!parse_double("", &item));
  assert(parse_double("123abc", &item));

  printf("Invalid parse tests passed\n");

  /* ---------- INVALID OPERATOR CHARACTER ---------- */
  stack_clear();
  stack_push(1);
  stack_push(2);

  assert(binary_operators['?'] == NULL);
  assert(libm_unary_operators['?'] == NULL);

  printf("Invalid operator lookup tests passed\n");

  printf("All invalid input tests passed\n\n");
}

int main() {
  test_stack();
  test_operators();
  test_mathlib();
  test_invalid_inputs();
  printf("\nAll tests passed successfully!\n");
  return 0;
}
