{
  configure_command: 'cmake -S . -B build-scan -DCMAKE_BUILD_TYPE=Debug',
  documentation_steps: [
    {
      name: 'Build project homepage',
      uses: 'actions/jekyll-build-pages@44a6e6beabd48582f863aeeb6cb2151cc1716697',
      with: {
        destination: 'build/html',
      },
    },
  ],
  env: {},
  setup_steps: [
    {
      name: 'Install build dependencies',
      run: 'sudo apt-get update\nsudo apt-get install -y freeglut3-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl1.2-compat-dev libsndfile1-dev portaudio19-dev\n',
    },
    {
      name: 'Install current CMake',
      run: 'pipx install cmake',
    },
  ],
}
