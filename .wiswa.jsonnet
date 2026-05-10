{
  uses_user_defaults: true,
  local top = self,
  // General settings
  project_type: 'c',
  want_claude: false,
  want_copilot: false,
  want_cursor: false,
  want_winget: false,
  clang_format_args: 'src/*.c src/audio/*.c src/graphics/*.c src/input/*.c src/screens/*.c src/*.h src/audio/*.h src/graphics/*.h src/input/*.h src/screens/*.h',

  // Shared
  github_username: 'Tatsh',
  security_policy_supported_versions: {},
  authors: [
    {
      'family-names': 'Udvare',
      'given-names': 'Andrew',
      email: 'audvare@gmail.com',
      name: '%s %s' % [self['given-names'], self['family-names']],
    },
  ],
  project_name: 'freeband',
  version: '0.0.2',
  description: 'An attempt at making a clone of Guitar Hero/Rock Band in C with SDL and OpenGL (archived project).',
  keywords: ['guitar hero', 'rock band', 'simulation'],

  // GitHub
  github+: {
    funding+: {
      ko_fi: 'tatsh2',
      liberapay: 'tatsh2',
      patreon: 'tatsh2',
    },
  },

  // C only
  vcpkg+: {
    dependencies: ['freeglut', 'libsndfile', 'portaudio', 'sdl12-compat'],
  },

  // Commitizen
  cz+: {
    commitizen+: {
      version_files+: ['snapcraft.yaml'],
    },
  },

  // Prettier
  prettierignore+: ['*.dtd', '*.rc'],

  // Snap
  snapcraft+: {
    apps+: {
      [top.project_name]+: {
        command: 'usr/bin/%s' % top.project_name,
        extensions: ['gnome'],
        plugs: [
          'audio-playback',
          'home',
          'opengl',
          'pulseaudio',
          'removable-media',
          'wayland',
          'x11',
        ],
      },
    },
    parts+: {
      [top.project_name]: {
        'build-packages': [
          'freeglut3-dev',
          'libsdl-image1.2-dev',
          'libsdl-ttf2.0-dev',
          'libsdl1.2-dev',
          'libsndfile1-dev',
          'pkg-config',
          'portaudio19-dev',
        ],
        'cmake-parameters': [
          '-DCMAKE_BUILD_TYPE=Release',
          '-DCMAKE_INSTALL_PREFIX=/usr',
        ],
        plugin: 'cmake',
        source: 'https://github.com/%s/%s.git' % [top.github_username, top.project_name],
        'source-tag': 'v%s' % top.version,
        'stage-packages': [
          'libglut3.12',
          'libportaudio2',
          'libsdl-image1.2',
          'libsdl-ttf2.0-0',
          'libsdl1.2debian',
          'libsndfile1',
        ],
      },
    },
  },
}
