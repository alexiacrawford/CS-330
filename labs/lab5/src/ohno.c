/*********************************************

CIS330: Lab 3

Implementation file for the error reporting system

*********************************************/

#include <ohno.h>

typedef enum {
  OHNO_WARNING,
  OHNO_SERIOUS,
  OHNO_FATAL
} ohno_severity_t;

struct ohno_state {
  FILE *output_stream;
  char *application_name;
  int error_number;
};

static struct ohno_state *state = NULL;

/*
 * Initialize the ohno error system with the given file stream and application name.
 *
 * This should allocate and populate the state structure.
 * Make sure to make a copy of `app_name` as we'll need to use this string later when `ohno()` is called.
 *
 * Feel free to return non-zero if anything went wrong (like not having sufficient memory).
 */
int
ohno_init(FILE* where_to, const char* app_name)
{
  state = (struct ohno_state*)malloc(sizeof(struct ohno_state));
  if (!state) return 1;

  state->output_stream = where_to;
  state->application_name = strdup(app_name);
  state->error_number = 0;

  if (!state->application_name) {
    free(state);
    state = NULL;
    return 1;
  }
  return 0;
}

/*
 * Free any memory allocated to the ohno error system.
 *
 * You allocated memory in `ohno_init()`, now you must give it back.
 */
void
ohno_free()
{
  if (state){
    free(state->application_name);
    free(state);
    state = NULL;
  }
}

/*
 * Report an error or warning given the current ohno error system settings (from ohno_init())
 *
 * This function should format `message` and `severity` along with the `app_name` string copied in `ohno_init()`
 * and write (print) a nice message on the saved `FILE *`.
 * The particular formating is up to you. Get creative if your like and feel free to add useful information
 * (e.g. error number or timestamp) to your report.
 */
void ohno(const char* message, ohno_severity_t severity)
{
  if (!state || !state->output_stream) return;

  const char* severity_str;
  switch (severity) {
    case OHNO_WARNING:
      severity_str = "WARNING";
      break;
    case OHNO_SERIOUS:
      severity_str = "SERIOUS";
      break;
    case OHNO_FATAL:
      severity_str = "FATAL";
      break;
    default:
      severity_str = "UNKNOWN";
  }

  // Increment the error counter
  state->error_number++;

  // Print the error message
  fprintf(state->output_stream, "%s: %s (Error #%d) - %s\n",
          state->application_name,
          severity_str,
          state->error_number,
          message);
  fflush(state->output_stream);