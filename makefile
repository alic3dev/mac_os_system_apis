makefiles=${shell find */ -name "makefile"}

directories=${dir ${makefiles}}
directories_make=${addprefix __make/,${directories}}
directories_clean=${addprefix __clean/,${directories}}

all: ${directories_make}

clean: ${directories_clean}

__make/%: .always
	cd "${patsubst __make/%,%,$@}" && make

__clean/%: .always
	cd "${patsubst __clean/%,%,$@}" && make clean

.always:
