# Maintainer: Salih Gerdan
pkgname=tetrahexyl
pkgver=git
pkgrel=1
pkgdesc=""
arch=('i686' 'x86_64')
url="https://github.com/salihgerdan/tetrahexyl"
license=('MIT')
depends=(sfml)
makedepends=(sfml)
source=(git+https://github.com/salihgerdan/tetrahexyl.git)
md5sums=("SKIP")

build() {
  cd "$srcdir/$pkgname"
  make
}

package() {
  cd "$srcdir/$pkgname"

  mkdir -p "$pkgdir/usr/share/tetrahexyl/"
  mkdir -p "$pkgdir/usr/share/tetrahexyl/resources"
  install resources/* "$pkgdir/usr/share/tetrahexyl/resources/"
  install tetrahexyl "$pkgdir/usr/share/tetrahexyl/"
  mkdir -p "$pkgdir/usr/share/applications"
  install tetrahexyl.desktop "$pkgdir/usr/share/applications"
  mkdir -p "$pkgdir/usr/bin/"
  echo "#!/bin/sh" > "$pkgdir/usr/bin/tetrahexyl"
  echo "cd /usr/share/tetrahexyl" >> "$pkgdir/usr/bin/tetrahexyl"
  echo "./tetrahexyl" >> "$pkgdir/usr/bin/tetrahexyl"
  chmod +x "$pkgdir/usr/bin/tetrahexyl"
  mv tetrahexyl_icon.png tetrahexyl.png
  mkdir -p "$pkgdir/usr/share/pixmaps/"
  install tetrahexyl.png "$pkgdir/usr/share/pixmaps/"
}
