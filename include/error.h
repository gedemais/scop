#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

enum	e_error_id
{
	ERR_NONE,
	ERR_INVALID_ARGC,
	ERR_OPENING_FILE,
	ERR_READING_FILE,
	ERR_MALLOC_FAILED,
	ERR_OUT_OF_BOUNDS_VALUE,
	ERR_INVALID_SETTINGS_SYNTAX,
	ERR_INVALID_SETTING_KEY,
	ERR_SETTING_KEY_NOT_FOUND,
	ERR_INVALID_OBJ_FILE_EXTENSION,
	ERR_INVALID_OBJ_LINE_ID,
	ERR_INVALID_PRIMITIVE_DESCRIPTION,
	ERR_NO_DEFINED_OBJECT,
	ERR_INVALID_OBJECT_NAME,
	ERR_INVALID_VERTEX_FORMAT,
	ERR_INVALID_VERTEX_INDEX_FOR_FACE,
	ERR_INVALID_NEWMTL_INSTRUCTION,
	ERR_MAX
};

typedef	struct	s_error
{
	char	msg[64];
	bool	usage;
}				t_error;

static const t_error	errors[ERR_MAX] = {
		[ERR_INVALID_ARGC] = {"Invalid number of arguments.", true},
		[ERR_OPENING_FILE] = {"Can not open file.", true},
		[ERR_READING_FILE] = {"Can not read file.", false},
		[ERR_MALLOC_FAILED] = {"malloc() call failed.", false},
		[ERR_INVALID_SETTINGS_SYNTAX] = {"Invalid syntax in Settings.toml.", false},
		[ERR_OUT_OF_BOUNDS_VALUE] = {"Out of bounds value in Settings.toml.", false},
		[ERR_INVALID_SETTING_KEY] = {"Unrecognized setting key.", false},
		[ERR_SETTING_KEY_NOT_FOUND] = {"Missing setting.", false},
		[ERR_INVALID_OBJ_LINE_ID] = {"Invalid line identifier in .obj file.", false},
		[ERR_INVALID_PRIMITIVE_DESCRIPTION] = {"Invalid face primitive description in .obj file.", false},
		[ERR_NO_DEFINED_OBJECT] = {"No defined object for vertex / face in obj file.", false},
		[ERR_INVALID_OBJECT_NAME] = {"Invalid object declaration in .obj file.", false},
		[ERR_INVALID_VERTEX_FORMAT] = {"Invalid vertex format in obj file.", false},
		[ERR_INVALID_VERTEX_INDEX_FOR_FACE] = {"Invalid vertex index for face in obj file.", false},
		[ERR_INVALID_OBJ_FILE_EXTENSION] = {"Invalid .obj file extension.", true},
		[ERR_INVALID_NEWMTL_INSTRUCTION] = {"Invalid newmtl instruction in .mtl file", false}
		//[] = {"", false}
		//[] = {"", false}
};

#endif
