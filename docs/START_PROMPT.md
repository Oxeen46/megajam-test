# Her yeni AI çalışma penceresi için

Repo klasörünü Codex çalışma alanı olarak aç. Aşağıdaki bloğu kopyala, köşeli parantezli alanları doldur ve gönder. Private repoya sadece URL göndermek erişim sağlamaz, AI'nin çalışma klasörünü okuyabildiğini kontrol et.

```text
Bu GitHub reposunda dört kişilik Unreal Engine C++ ekibinin bir üyesi olarak çalışıyoruz.

Benim adım / GitHub hesabım: [AD VE HESAP]
Yerel repo klasörü: [TAM KLASÖR YOLU]
Bana atanmış branch: [work/safa VEYA work/member-2 VEYA work/member-3]
Bu oturumdaki görevim: [YAPILACAK İŞ]

Önce AGENTS.md, README.md, docs/PROJECT.md ve varsa kendi
docs/handoffs/<branch-son-adi>.md dosyamı oku. İlgili alt dizinlerin ajan
talimatlarını, gerçek dosyaları ve son commitleri incele. Eski sohbet
varsayımlarını güncel dosyalarla doğrula.

Git durumunu, aktif branch'i, remote'u ve yerel değişiklikleri kontrol et.
Ağ varsa origin'i fetch et. Temiz çalışma alanında kendi branch'imi güncel
origin/main ile merge et. Yanlış branch, belirsiz değişiklik, erişim engeli
veya ortak binary dosya sahipliği sorunu varsa önce netleştir.

Aktif proje kökteki MyProject.uproject. Oyun mantığını C++ ile geliştir.
Anladığın görevi, kullanacağın branch'i ve dokunacağın dosyaları kısa yaz.
Ardından görev kapsamında çalış ve uygun doğrulamayı yap.

Bitince kendi devir notumu güncelle. Sadece bu görevin dosyalarını inceleyip
stage et, kendi branch'ime commit ve push yap, main hedefli PR aç.
Bu oturumda bu işlemlere yetki veriyorum. Birleştirmeyi Horizon yapacak.
PR aracın yoksa hazır PR açıklamasını ve branch adını ver. Erişemediğin
işlemi yapılmış gibi raporlama. Test sonuçlarını ve kalan işi belirt.
```

Safa branch alanına `work/safa` yazar. Diğer iki kişi kendilerine atanmış branch'i yazar. Bilinmeyen bir branch sahibini tahmin etme.

Horizon PR incelemesi için branch alanına `main`, görev alanına PR numarasını yazar. Son paragrafı aşağıdakiyle değiştirir.

```text
Bu oturum entegrasyon incelemesi içindir. Belirttiğim PR'nin diff'ini,
main ile ilişkisini ve testlerini kontrol et. Gerekli doğrulamayı PR'nin
branch'inde yap. İnceleme sonucunu ve eksikleri yaz. Birleştirme yetkisini
bu mesajımda açıkça vermişsem ve kontroller geçerse merge commit ile
birleştir. Kalıcı kişisel branch'leri koru.
```
