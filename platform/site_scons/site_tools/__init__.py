
import SCons.Builder
import SCons.Scanner

SourceFileScanner = SCons.Scanner.Base({}, name='SourceFileScanner')

def createASMBuilders(env):
    """This is a utility function that creates the StaticObject
    and SharedObject Builders in an Environment if they
    are not there already.

    If they are there already, we return the existing ones.

    This is a separate function because soooo many Tools
    use this functionality.

    The return is a 2-tuple of (StaticObject, SharedObject)
    """
    
    env['BUILDERS']['ASMPREFIX'] = ''
    env['BUILDERS']['ASMSUFFIX'] = 'asm'
    
    try:
        asm_file = env['BUILDERS']['ASMFile']
    except KeyError:
        # asm_com = SCons.Action.Action('$JARCOM', '$JARCOMSTR')
        asm_file = SCons.Builder.Builder(action = {},
                                         emitter = {},
                                         prefix = '$ASMPREFIX',
                                         suffix = 'asm',
                                         src_builder = ['CFile', 'CXXFile'],
                                         source_scanner = SourceFileScanner,
                                         single_source = 1)
        env['BUILDERS']['ASMFile'] = asm_file

    return asm_file
