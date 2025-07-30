name=key_logging

directory_include=include
directory_objects=objects
directory_output=output

file_output=${directory_output}/${name}

files_sources=${wildcard sources/*.c}
files_objects=${patsubst sources/%.c,objects/%.o,${files_sources}}

frameworks=CoreFoundation CoreGraphics

cc=clang
c_flags=-O3
c_flags_source=${c_flags} -I${directory_include}
c_flags_output=${c_flags} ${addprefix -framework ,${frameworks}}

strip=strip
strip_flags=-u -r

${name}: ${file_output}

run: ${file_output} .always
	./${file_output}

${file_output}: ${files_objects} ${directory_output}
	${cc} ${c_flags_output} ${files_objects} -o $@

objects/%.o: sources/%.c ${directory_objects}
	${cc} ${c_flags_source} -c $< -o $@

directories: ${directory_objects} ${directory_output}

${directory_objects}:
	mkdir -p ${directory_objects}

${directory_output}:
	mkdir -p ${directory_output}

clean: clean_objects clean_output

clean_objects:
	-rm -r ${directory_objects}

clean_output:
	-rm -r ${directory_output}

.always:

