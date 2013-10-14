"""SCons.Tool.cc1plus

Tool-specific initialization for cc1plus.

There normally shouldn't be any need to import this module directly.
It will usually be imported through the generic SCons.Tool.Tool()
selection method.

"""

import os.path
import re
import subprocess

import SCons.Tool
import SCons.Defaults
import SCons.Util

import CWTools

compilers = ['cc1plus']

CXXSuffixes = ['.cpp', '.cc', '.cxx', '.c++', '.C++', '.mm']
if SCons.Util.case_sensitive_suffixes('.c', '.C'):
    CXXSuffixes.append('.C')

def iscplusplus(source):
    if not source:
        # Source might be None for unusual cases like SConf.
        return 0
    for s in source:
        if s.sources:
            ext = os.path.splitext(str(s.sources[0]))[1]
            if ext in CXXSuffixes:
                return 1
    return 0

def generate(env):
    """Add Builders and construction variables for cc1plus to an Environment."""
    asm_file = CWTools.createASMBuilders(env)

    import SCons.Tool
    import SCons.Tool.cc
    
    for suffix in CXXSuffixes:
        asm_file.add_action(suffix, SCons.Defaults.CXXAction)
#        asm_file.add_emitter(suffix, SCons.Defaults.StaticObjectEmitter)

    env['BUILDERS']['StaticObject'].add_src_builder(asm_file)
    env['BUILDERS']['Object'].add_src_builder(asm_file)
    env['BUILDERS']['SharedObject'].add_src_builder(asm_file)

    SCons.Tool.cc.add_common_cc_variables(env)

    env['CXX']        = env.Detect(compilers)
    env['CXXFLAGS']   = SCons.Util.CLVar('')
    env['CXXCOM'] = '$CXX -o $TARGET $CXXFLAGS $CCFLAGS $_CCCOMCOM $SOURCES'
    env['SHCXX']      = '$CXX'
    env['SHCXXFLAGS'] = SCons.Util.CLVar('$CXXFLAGS')
    env['SHCXXCOM'] = '$SHCXX -o $TARGET $SHCXXFLAGS $SHCCFLAGS $_CCCOMCOM $SOURCES'

    env['CPPDEFPREFIX']  = '-D'
    env['CPPDEFSUFFIX']  = ''
    env['INCPREFIX']  = '-I'
    env['INCSUFFIX']  = ''
    env['INCSYSPREFIX']  = '-isystem'
    env['INCSYSSUFFIX']  = ''
#    env['SHOBJSUFFIX'] = '.os'
#    env['OBJSUFFIX'] = '.o'
#    env['STATIC_AND_SHARED_OBJECTS_ARE_THE_SAME'] = 0

    env['CXXFILESUFFIX'] = '.cc'

    env['_CPPSYSINCFLAGS'] = '$( ${_concat(INCSYSPREFIX, CPPSYSPATH, INCSYSSUFFIX, __env__, RDirs, TARGET, SOURCE)} $)'
    env['_CCCOMCOM'] = '$CPPFLAGS $_CPPDEFFLAGS $_CPPSYSINCFLAGS $_CPPINCFLAGS'

    # determine compiler version
    if env['CXX']:
        cc1plus_path = env.WhereIs(env['CXX'])
        pipe = SCons.Action._subproc(env, [cc1plus_path, '-quiet', '-version', 'NUL'],
                                     stdin = 'devnull',
                                     stderr = subprocess.PIPE,
                                     stdout = 'devnull')
        if pipe.wait() != 0: return
        line = pipe.stderr.readline()
        match = re.search(r'[0-9]+(\.[0-9]+)+', line)
        if match:
            env['CXXVERSION'] = match.group(0)

def exists(env):
    return env.Detect(compilers)
