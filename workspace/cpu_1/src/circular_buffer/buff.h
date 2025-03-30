#include <stdint.h>

typedef struct {
	int head;
	int tail;
	int max_size;
	uint8_t *buff;
	int element_size;
	int capacity;
} circular_buff_t;

circular_buff_t* init(int buff_size, int element_size, int capacity);
int push (circular_buff_t* buffer, void* element);
int pop(circular_buff_t* buffer, void* element);
int is_full(circular_buff_t* buffer);
int is_empty(circular_buff_t* buffer);
