(import 'defaults.libsonnet') + {
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
  version: '0.0.0',
  description: 'An attempt at making a clone of Guitar Hero/Rock Band in C with SDL and OpenGL (archived project).',
  keywords: ['guitar hero', 'rock band', 'simulation'],
  social+: {
    mastodon+: { id: '109370961877277568' },
  },

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
    dependencies: ['sdl1'],
  },
}
