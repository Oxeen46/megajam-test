# MegaJam ekip çalışma alanı

Dört kişilik Unreal Engine C++ ekip provası. Proje dosyaları GitHub'da, indirilebilir oyun build'leri itch.io'da tutulur.

## Başlangıç belgeleri

- [Her yeni AI sohbetinde kullanılacak prompt](docs/START_PROMPT.md)
- [Ajan çalışma kuralları](AGENTS.md)
- [Proje durumu ve kararlar](docs/PROJECT.md)
- [Model, ses, görsel ve belge yükleme](TeamUploads/README.md)

## Ekip ve branch düzeni

| Kişi | Branch | Görev |
| --- | --- | --- |
| Horizon | `main` | PR'leri inceler ve ortak sürüme birleştirir |
| Safa / Oxeen46 | `work/safa` | Kendi görevlerini geliştirir ve PR açar |
| Üye 2 | `work/member-2` | Kendi görevlerini geliştirir ve PR açar |
| Üye 3 | `work/member-3` | Kendi görevlerini geliştirir ve PR açar |

Üye 2 ve 3 yer tutucu isimlerdir. Horizon bu branch'leri birer kişiye atar ve bu tablodaki isimleri günceller. Branch adını değiştirmek zorunlu değildir. Branch oluşturmak repo erişimi vermez. Her üye GitHub davetini kendi hesabıyla kabul eder.

Horizon günlük oyun geliştirme işi de yapacaksa `work/horizon` açarak aynı PR akışını kullanır. `main` ortak, derlenebilir sürümdür.

## İlk kurulum

1. GitHub davetini kabul et. GitHub Desktop ve Git for Windows kur, kendi hesabınla giriş yap.
2. Ekiple aynı Unreal Engine sürümünü kullan. Hedef **5.8.4**. `.uproject` içindeki `5.8` alanı patch sürümünü garanti etmez, Launcher'dan tam sürümü kontrol et.
3. Unreal sürümünün desteklediği Visual Studio C++ toolchain'ini, Windows SDK'yı ve C++ oyun geliştirme bileşenlerini kur. Derleyici hatasında tam hata çıktısını paylaş.
4. GitHub Desktop'ta **File → Clone repository → URL** üzerinden `https://github.com/Oxeen46/megajam-test.git` adresini klonla. Yerel kısa bir klasör seç, örneğin `C:\Dev\megajam-test`.
5. Repo klasöründe **Open Git Bash here** ile terminal aç ve aşağıdaki komutları çalıştır.

```bash
git lfs install
git lfs pull
```

LFS indirmesi hata verdiyse Unreal'ı açmadan çöz. `.gitattributes` ortak ayar dosyasıdır, herkesin yeniden track komutu yazması gerekmez.

6. GitHub Desktop **Current branch** alanından sana atanmış branch'i seç. Görünmüyorsa **Fetch origin** yap. Henüz oluşturulmadıysa güncel main'den atanmış isimle **New branch → Publish branch** yap.
7. Repo kökündeki **`MyProject.uproject`** dosyasını aç. Sürüm sorulursa ekip sürümünü seç. Modülleri derlemeyi sorarsa **Yes** seç. Derleme başarısızsa hatayı paylaş.
8. `MegaJamTest/MegaJamTest.uproject` önceki kurulum denemesidir. Ortak çalışma için kökteki `MyProject.uproject` seçildi.

Unreal'da ayrıca arkadaş daveti gerekmez. Herkes GitHub'dan aldığı proje kopyasını kendi bilgisayarında düzenler. Değişiklikler commit, push ve PR ile paylaşılır. itch.io admin erişimi oyun sayfası yönetimi içindir.

## Her çalışma günü

1. Branch değiştirmeden veya güncellemeleri almadan önce Unreal'da kaydet ve editörü kapat.
2. GitHub Desktop'ta repo ve kendi branch'ini kontrol et. Changes doluysa hangi işe ait olduğunu belirle. Çalışmayı silme veya rastgele stash yapma.
3. **Fetch origin**, gerekiyorsa **Pull origin** yap. **Branch → Merge into current branch** üzerinden güncel `origin/main`i kendi branch'ine al. Menü yalnızca yerel main'i gösteriyorsa temiz durumda main'e geç, Pull origin yap, kendi branch'ine dön ve main'i merge et.
4. [Başlangıç promptunu](docs/START_PROMPT.md) doldurup AI'ye gönder. AI'nin bu repo klasörüne eriştiğini doğrula.
5. Ekibe hangi harita ve dosyada çalışacağını bildir. Aynı `.umap` veya `.uasset` üzerinde aynı anda düzenleme yapmayın. Ortak C++ sınıflarındaki işleri de koordine edin.
6. Çalış, kaydet, derle ve göreve uygun testi yap. AI kendi devir dosyasını güncellesin.
7. GitHub Desktop **Changes** listesini incele, ilgili dosyaları seç, Summary yaz, **Commit to kendi-branchin → Push origin** yap.
8. **Preview Pull Request / Create Pull Request** ile hedefi `main`, kaynağı kendi branch'in olan PR aç. Şablondaki iş ve test bilgilerini doldur.
9. Horizon birleştirdikten sonra güncel `origin/main`i kendi branch'ine merge et. Sonraki göreve aynı kişisel branch'te devam edebilirsin. Aynı branch'te ikinci işe geçmeden önceki PR'yi tamamla.

Temiz çalışma alanı için Git Bash karşılığı, Safa örneğiyle aşağıdadır.

```bash
git switch work/safa
git fetch origin
git pull --ff-only origin work/safa
git merge origin/main
git lfs pull
```

Çakışma çıkarsa paylaş. Binary Unreal dosyalarını metin düzenleyicide birleştirmeyin. Push değişiklikleri kendi uzak branch'ine gönderir. PR'nin main'e birleşmesi ayrı bir adımdır.

## Horizon'ın birleştirme akışı

1. PR hedefinin main olduğunu, değişen dosyaları ve test sonuçlarını kontrol et.
2. Harita, ortak Content, input, GameMode, Config ve plugin değişikliklerinin diğer işlerle ilişkisini incele. Gerekiyorsa PR branch'ini yerelde aç, derle ve çalıştır.
3. PR güncel main'in gerisindeyse yazardan main'i kendi branch'ine almasını iste. Çakışmayı ilgili dosyanın sahibi çözer.
4. **Create a merge commit** yöntemiyle birleştir. Kalıcı kişisel branch'leri silme. Otomatik branch silme kapalı kalsın.
5. Main'i yerelde güncelle ve ilgili derleme/açılış testini yap. Hatalı birleşmede ilgili PR'yi revert ederek geri almayı değerlendir.

AGENTS.md teknik erişim kısıtlaması oluşturmaz. Private repoda zorunlu PR onayı ve branch koruması hesabın planına bağlıdır. Plan destekliyorsa main için PR ve bir onay isteyin, force push ve silmeyi kapatın. Mevcut plan ve Horizon'ın kullanıcı adı doğrulanmadan koruma veya CODEOWNERS kurulmuş sayılmaz.

## Klasörler

| Yol | İçerik |
| --- | --- |
| `MyProject.uproject` | Aktif Unreal projesi |
| `Source/MyProject/` | C++ kaynakları |
| `Config/` | Paylaşılan proje ayarları |
| `Content/` | Unreal varlıkları ve haritaları |
| `TeamUploads/` | Modeller, sesler, görseller, belgeler |
| `docs/` | Proje durumu, prompt, kişi bazlı devir notları |
| `MegaJamTest/` | Önceki kurulum denemesi |

`Binaries`, `Intermediate`, `DerivedDataCache`, `Saved`, `.vs`, `.idea`, `.sln` ve `.slnx` yerelde üretilir, GitHub'a yüklenmez. `.gitignore` ve `.gitattributes` ortak tutulur. LFS depolama ve aktarım kullanımını repo sahibi takip eder.

## C++ doğrulama

Örnek PowerShell komutu repo kökünde çalıştırılır. Motor yolun farklıysa düzelt. Unreal'ı kapatarak tam derleme yap.

```powershell
& 'C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat' MyProjectEditor Win64 Development "$(Get-Location)\MyProject.uproject" -WaitMutex
```

Derlemeden sonra ilgili davranışı editörde dene. Paket kontrolü gerekiyorsa Windows Development build al, çıktıyı repo dışında tut. `.exe` ve beraberindeki dosyalar itch.io'ya yüklenir. Bu repo kurulumu bir oyun derleme testi yerine geçmez.

## Kaynaklar

- [GitHub Pull Requests](https://docs.github.com/en/pull-requests)
- [Git LFS](https://docs.github.com/en/repositories/working-with-files/managing-large-files/configuring-git-large-file-storage)
- [Branch koruması](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches)
- [Codex AGENTS.md](https://developers.openai.com/codex/guides/agents-md/)
