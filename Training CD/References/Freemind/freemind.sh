#!/bin/sh
# 2004-02-13, modified for Debian by deb@zorglub.s.bawue.de
# 2004-06-19, rewritten for Linux/UN*X by deb@zorglub.s.bawue.de
#             (based on Jan Schulz's input)
# 2004-11-28, minor changes for version 0.8.0 by deb@zorglub.s.bawue.de
# 2005-01-08, removed bashims to make script POSIX conform
# 2005-01-16, added usage of FREEMIND_BASE_DIR variable
# 2005-02-18, add -Dfreemind.base.dir to make plugins work, add some ""
#             and enhance debug mode.

_debug() {
	if [ -n "${DEBUG}" ]
	then
		echo "DEBUG:   $1" >&2 
		shift
		for text in "$@"
		do
			echo "         ${text}" >&2
		done
	fi
}

_error() {
	echo "ERROR:   $1" >&2
	shift
	for text in "$@"
	do
		echo "         ${text}" >&2
	done
}

findjava() {
	# We try hard to find the proper 'java' command
	if [ -n "${JAVACMD}" ] && [ -x "${JAVACMD}" ]
	then
		_debug "Using \$JAVACMD to find java virtual machine."
	elif [ -n "${JAVA_BINDIR}" ] && [ -x "${JAVA_BINDIR}/java" ]
	then
		JAVACMD="${JAVA_BINDIR}/java"
		_debug "Using \$JAVA_BINDIR to find java virtual machine."
	elif [ -n "${JAVA_HOME}" ] && [ -x "${JAVA_HOME}/bin/java" ]
	then
		JAVACMD="${JAVA_HOME}/bin/java"
		_debug "Using \$JAVA_HOME to find java virtual machine."
	else
		JAVACMD=$(which java)
		if [ -n "${JAVACMD}" ] && [ -x "${JAVACMD}" ]
		then
			_debug "Using \$PATH to find java virtual machine."
		elif [ -x /usr/bin/java ]
		then
			_debug "Using /usr/bin/java to find java virtual machine."
			JAVACMD=/usr/bin/java
		fi
	fi

	# if we were successful, we return 0 else we complain and return 1
	if [ -n "${JAVACMD}" ] && [ -x "${JAVACMD}" ]
	then
		_debug "Using '$JAVACMD' as java virtual machine..."
		if [ -n "${DEBUG}" ]
		then
			"$JAVACMD" -version
		fi
		return 0
	else
		_error "Couldn't find a java virtual machine," \
		       "define JAVACMD, JAVA_BINDIR, JAVA_HOME or PATH."
		return 1
	fi
}

_source() {
	if [ -f "$1" ]
	then
		_debug "Sourcing '$1'."
		. "$1"
	fi
}

_debug "Freemind parameters are '${@}'."
_debug "$(uname -a)"

_source /etc/freemind/freemindrc
_source ~/.freemind/freemindrc

findjava
if [ $? -ne 0 ]
then
	exit 1
fi

freepath=$(dirname "$0")
freepath="${freepath%/bin}" # nothing happens if freemind is not installed
                            # under something/bin

# we try different possibilities to find freemind.jar
for jar in "${FREEMIND_BASE_DIR}" \
	"${freepath}" "${freepath}/share/freemind" "${freepath}/freemind"
do
	if [ -f "${jar}/lib/freemind.jar" ]
	then
		freedir="${jar}"
		_debug "Freemind Directory is '${jar}'."
		break
	fi
done

if [ -z "${freedir}" ]
then
	_error "Couldn't find freemind under '${freepath}'."
	exit 1
fi

if [ ! -f ~/.freemind/patterns.xml ] && [ -f /etc/freemind/patterns.xml ]
then
	if [ ! -d ~/.freemind ]
	then
		_debug "Creating directory ~/.freemind."
		mkdir -p ~/.freemind
	fi
	_debug "Copying patterns.xml to ~/.freemind."
	cp /etc/freemind/patterns.xml ~/.freemind/patterns.xml
fi

# The CLASSPATH also lets one specify additional jars, which is good, if
# you want to add a new Look&Feel jar (the motif one is so ugly...).
# 
CLASSPATH="${ADD_JARS}:${CLASSPATH}:${freedir}/lib/freemind.jar:\
${freedir}/lib/ant/lib/jaxb-api.jar:\
${freedir}/lib/ant/lib/jaxb-impl.jar:\
${freedir}/lib/ant/lib/jaxb-libs.jar:\
${freedir}/lib/ant/lib/namespace.jar:\
${freedir}/lib/ant/lib/relaxngDatatype.jar:\
${freedir}/lib/ant/lib/xsdlib.jar:\
${freedir}/lib/ant/lib/jax-qname.jar:\
${freedir}/lib/ant/lib/sax.jar:\
${freedir}/lib/ant/lib/dom.jar:\
${freedir}/lib/forms-1.0.5.jar:\
${freedir}"
_debug "Calling: '${JAVACMD} -Dfreemind.base.dir=${freedir} -cp ${CLASSPATH} freemind.main.FreeMind  $@'."
"${JAVACMD}" -Dfreemind.base.dir="${freedir}" -cp "${CLASSPATH}" freemind.main.FreeMind "$@"
