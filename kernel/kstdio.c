#define __KTW_COLUMNS 80
#define __KTW_LINES 25

#include <video.h>
#include <fcntl.h>
#include <kfcntl.h>

static struct x86_video_char __ktw_buffer[__KTW_COLUMNS*__KTW_LINES];
static text_window __ktw = {0, 0, __KTW_COLUMNS, __KTW_LINES, 0, 0, 0,
                            DEFAULT_ATTRIBUTE_VALUE, 1, __ktw_buffer};
static text_window *ktw = &__ktw;

void itoa (char *buf, int base, int d) {
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

	/* If %d is specified and D is minus, put `-' in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	} else if (base == 'x') {
		divisor = 16;
	}

	/* Divide UD by DIVISOR until UD == 0. */
	do {
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while (ud /= divisor);

	/* Terminate BUF. */
	*p = 0;

	/* Reverse BUF. */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

void kprintf(const char *format, ...) {
	switchBuffer(1);
  char **arg = (char **) &format;
  int c;
  char buf[20];

  arg++;

  while ((c = *format++) != 0)
    {
      if (c != '%')
        kputchar (ktw, c);
      else
        {
          char *p;

          c = *format++;
          switch (c)
            {
            case 'd':
            case 'u':
            case 'x':
              itoa (buf, c, *((int *) arg++));
              p = buf;
              goto string;
              break;

            case 's':
              p = *arg++;
              if (! p)
                p = "(null)";

            string:
              while (*p)
                kputchar (ktw, *p++);
              break;

            default:
              kputchar (ktw, *((int *) arg++));
              break;
            }
        }
    }
}

size_t write_screen(open_file_descriptor *ofd, const void *buf, size_t count) {
	size_t i;
	for (i = 0; i < count && *(char *)buf != '\0'; i++) {
		if (*(char *)buf == '\b') {
			backspace((text_window *)(ofd->extra_data), *((char *)(buf))); // Devrait tenir compte de la diff entre \t et les autres caractères.
		} else {
			kputchar((text_window *)(ofd->extra_data), *(char *)buf);
		}

		buf++;
	}
	return count;
}

size_t read_screen(open_file_descriptor *ofd, void *buf, size_t count) {
	char c;
	unsigned int i;
	int j = 0;

	while(count--) {
		while(ofd->current_octet_buf == 0 || ofd->buffer[ofd->current_octet_buf-1] != '\n'); // Serait plus sympa avec une sémaphore :P
		c = ofd->buffer[0];
		ofd->current_octet_buf--;

		for(i = 0; i < ofd->current_octet_buf; i++) {
			ofd->buffer[i] = ofd->buffer[i+1];
		}
		((char*)buf)[j++] = c;
	}

	return j;
}

