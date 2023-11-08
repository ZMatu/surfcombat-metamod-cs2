<div align="center">
    <h3>A metamod plugin for Surf Combat CS2</h3>
</div>

#### Requirements
- [Metamod:Source](https://www.sourcemm.net/downloads.php/?branch=master) (build 1219 or higher)
- CS2 server with __-insecure__ launch option (for surf maps)
#### Win-64

```sh
git clone https://github.com/mEldevlp/surfcombat-metamod-cs2.git
cd surfcombat-metamod-cs2
git submodule update --init --recursive
```

#### Linux
```sh
git clone https://github.com/mEldevlp/surfcombat-metamod-cs2.git
cd surfcombat-metamod-cs2
git submodule update --init --recursive
mkdir build && cd build
CC=gcc CXX=g++ python3 ../configure.py --hl2sdk-root "../" -s cs2
ambuild
```

#### Features

- [x] Red and Blue player models
- [ ] Hide players and legs ( !hide & !legs )
- [ ] Deathmatch system
- [ ] Admin\VIP system
- [ ] Chat player prefix
- [ ] Ranking
- [ ] +strafe* (no-angle surfing)
