# Ekip kaynak dosyaları

Dosyaları kendi branch'inde ekle. PR birleşince main'de görünür. `.gitkeep` boş dizini Git'te tutar.

| Klasör | Dosyalar |
| --- | --- |
| `Models/<kisi>/` | Blender, FBX, GLB ve model kaynakları |
| `Audio/<kisi>/` | WAV, OGG, MP3, ses ve müzik |
| `Images/<kisi>/` | Dokular, çizimler, referans görseller |
| `Documents/<kisi>/` | Fikirler, tasarım notları, PDF ve belgeler |

1. İlgili dizinde kendi isim klasörünü oluştur. Örnek `TeamUploads/Models/safa/crate.blend`. Kısa İngilizce dosya adları ve alt çizgi kullan.
2. Yanına `crate-source.md` kaynak notu koy. Üretici, kaynak bağlantısı veya kendi üretimin olduğu, lisans/kullanım izni, AI kullanımı varsa araç ve yöntem, amaç ve varsa Content karşılığını yaz.
3. `git check-attr filter -- TeamUploads/Models/safa/crate.blend` ile binary dosyada `filter: lfs` çıktısını kontrol et. Yeni biçim için LFS kuralını ilk commit'ten önce ekle.
4. GitHub Desktop'tan kendi branch'ine commit/push yap, PR aç. LFS depolama ve aktarım kullanımını ekip sorumlusuyla takip et.

TeamUploads'a koyulan kaynak otomatik oyuna eklenmez. Unreal'da ayrıca editörden Content'e import edilir. `.uasset` ve `.umap` oyun dosyalarının yeri Content'tir.

Oynanabilir build, proje yedek ZIP'i, cache, şifre ve API anahtarı yüklemeyin. Build dağıtımı itch.io üzerinden yapılır. Paylaşım izni olmayan üçüncü taraf dosyaları yerine kaynak bağlantısı ve kurulum yönergesi ekleyin.
