# Ekip ajan talimatları

## Proje ve başlangıç

- Kullanıcıyla Türkçe ve anlaşılır konuş. Bu repo dört kişilik game jam hazırlık provasıdır. Final tema ve oyun tasarımı henüz belirlenmedi.
- Aktif proje kökteki `MyProject.uproject`, kod `Source/MyProject`, varlıklar `Content`, ayarlar `Config` altındadır. `MegaJamTest/` önceki kurulum denemesidir. Görev açıkça hedeflemiyorsa orada çalışma.
- Ekip hedefi Unreal Engine 5.8.4, Windows x64, C++ oyun mantığıdır. Mevcut Blueprint örnek varlıklarını referanslarını incelemeden silme. Yeni oyun mantığını C++ ile uygula. Blueprint mantığı gerektiren yeni kararı kullanıcıyla netleştir.
- Önce README.md, docs/PROJECT.md, varsa kendi docs/handoffs/<branch-son-adi>.md dosyanı, ilgili alt dizin talimatlarını ve son commitleri oku. AGENTS.override.md varsa ek etkisini kontrol et.
- `git status --short --branch`, `git remote -v` ve `git branch --show-current` ile durumu doğrula. Kişi, branch veya görev eksikse kod değiştirmeden sor.
- Ağ erişimi varsa `git fetch origin` yap. Erişim veya Unreal aracı eksikse bildir. Yapılmayan kontrolü yapılmış gibi raporlama.

## Branch kuralları

- Horizon main entegrasyonunu yönetir. Safa `work/safa`, diğer iki kişi kendilerine atanmış `work/member-2` ve `work/member-3` üzerinde çalışır. Aynı branch iki kişiye atanmaz.
- Kod yazan ajan kullanıcının branch'inde çalışır. Yanlış branch veya belirsiz yerel değişiklik varsa otomatik taşıma, stash, silme veya checkout yapma. Önce doğru çalışma alanını netleştir.
- Temiz durumda atanmış branch'e geç, varsa uzak branch'i takip et. Başkasının branch'ini güncelleme.
- Görev başında ve PR öncesinde temiz çalışma alanında güncel `origin/main`i `git merge origin/main` ile kendi branch'ine al. Paylaşılmış branch'te rebase ve force push kullanma.
- Günlük görevler kendi branch'inden main hedefli PR ile teslim edilir. Birleştirmeyi Horizon inceler. Horizon'ın ajanı ancak o oturumda birleştirme yetkisi verilmişse PR'yi birleştirir.
- Merge commit yöntemi kullanılır, kalıcı kişisel branch'ler korunur. Yazar birleşme sonrası main'i kendi branch'ine tekrar merge eder.
- `git reset --hard`, `git clean`, branch silme ve uzak geçmişi yeniden yazmayı normal akışta kullanma. Kullanıcı değişikliklerini koru.
- Aynı klasörde iki eşzamanlı ajan çalıştırma. İkinci oturum için ayrı clone/worktree ve ayrı görev branch'i gerekir. Açık Unreal editörü kendi proje klasörüne bağlıdır.

## Dosya sahipliği ve Unreal

- Ekip görev başlamadan ortak varlık ve harita sahipliğini iletişim kanalında paylaşır. Görev/PR bilgisini kontrol et. Ortak binary dosyanın sahibi belirsizse kullanıcıya sor.
- `.uasset`, `.umap`, `.blend` dosyalarını metin olarak merge etme. Çakışmada sessizce ours/theirs seçme. Doğru sürümü sahibiyle belirleyip diğer değişikliği editörde uygula.
- Harita, input, GameMode, `.uproject`, `.Build.cs` ve Config değişikliklerini PR'de belirt. World Partition dış aktör dosyalarını ilgili haritayla birlikte değerlendir.
- Unreal içeriğini editörden taşı/yeniden adlandır. Redirector ve referansları kontrol et. Content dosyalarını Windows'tan topluca taşıma.
- LFS pointer dosyalarıyla editörü açma. Gerçek varlıkların indirildiğini kontrol et. Git ignore ve LFS kurallarına uy.
- Motor yükseltmesi, plugin, yeni bağımlılık ve geniş refactor için görev kapsamını kontrol et. İlgisiz değişiklik yapma.

## Yükleme ve bitiriş

- TeamUploads/README.md kurallarını uygula. Kaynak, üretici, lisans ve AI kullanımı bilgisini dosyanın yanında Markdown ile yaz. Gizli anahtar ve kişisel hesap bilgisi ekleme.
- Kaynak dosyanın TeamUploads'a konması otomatik Unreal import işlemi yapmaz. Görev kapsamında gerekliyse Content'e import et, bağlantısını not et. Build ve proje yedek ZIP'lerini TeamUploads'a koyma.
- C++ değişikliğinde ilgili hedefi derle. Harita/varlık değişikliğinde editör kontrolü yap. Paketlemeyi etkileyen görevde Windows Development build doğrula. Sadece belge değişikliğinde diff/link kontrolü yeterlidir.
- Live Coding sonucunu tam derleme sonucu gibi sunma. Yapamadığın testi ve nedenini açıkça yaz.
- `git diff --check` ve staged diff'i incele. İlgili dosyaları açık yollarıyla stage et. Görev dışı dosyaları commit'e katma.
- Kullanıcı işi tamamlayıp göndermeni istediyse kendi branch'inde commit ve push yap. Yetki yerel düzenlemeyle sınırlıysa koru. Günlük görevde main'e doğrudan push yapma.
- PR açıklamasında .github/pull_request_template.md kullan. PR aracın yoksa hazır açıklamayı ve branch'i kullanıcıya ver. PR açılmış gibi davranma.
- Oturum sonunda kendi docs/handoffs/<branch-son-adi>.md dosyanı güncelle. Örneğin work/safa için safa.md. Tarih, görev, değişen dosyalar, karar, test sonucu, kalan iş ve sonraki adımı kısa yaz. Tüm sohbeti kopyalama.
- Son yanıtta branch, commit/push/PR durumu, doğrulama ve varsa engeli belirt. Sohbet hafızasını repo dosyalarının yerine kullanma.
