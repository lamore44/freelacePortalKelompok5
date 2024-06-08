      ________  _______   _______  ___      ___  __     ______    _______  
 /"       )/"     "| /"      \|"  \    /"  ||" \   /" _  "\  /"     "| 
(:   \___/(: ______)|:        |\   \  //  / ||  | (: ( \___)(: ______) 
 \___  \   \/    |  |_____/   ) \\  \/. ./  |:  |  \/ \      \/    |   
  __/  \\  // ___)_  //      /   \.    //   |.  |  //  \ _   // ___)_  
 /" \   :)(:      "||:  __   \    \\   /    /\  |\(:   _) \ (:      "| 
(_______/  \_______)|__|  \___)    \__/    (__\_|_)\_______) \_______) 
                                                                       
      ________  _______    __    __    _______   _______    _______    
     /"       )|   __ "\  /" |  | "\  /"     "| /"      \  /"     "|   
    (:   \___/ (. |__) :)(:  (__)  :)(: ______)|:        |(: ______)   
     \___  \   |:  ____/  \/      \/  \/    |  |_____/   ) \/    |     
      __/  \\  (|  /      //  __  \\  // ___)_  //      /  // ___)_    
     /" \   :)/|__/ \    (:  (  )  :)(:      "||:  __   \ (:      "|   
    (_______/(_______)    \__|  |__/  \_______)|__|  \___) \_______)  


    -> Alur Program 
      ->Pada menu register pengguna akan diverifikasi mendaftar sebagai freelancer atau user biasa (pengguna TIDAK BISA RANGKAP STATUS)
      ->Ketika login sebagai freelancer maka terdapat 6 menu yakni:
        1. view profile
        2. view order
        3. add service
        4. delete service
        5. complete order
        6. cancel order
          -> Ketika masuk view profile hanya menampilkan username, balance dan role (freelancer/user)
          -> Ketika masuk view order maka menampilkan pesanan dari user dalam bentuk indeks
          -> Ketika masuk add service maka pengguna dapat memasukkan nama jasa, deskripsi jasa, dan harga dari jasanya
          -> Ketika masuk delete service maka pengguna memilih sesuai indeks dari jasa yang telah dimasukkan untuk dihapus
          -> Ketika masuk complete order maka pengguna dapat memilih dari pesanan yang masuk dari user untuk diselesaikan, jika diselesaikan maka freelancer              mendapatkan uang dari user yang telah dibayarkan dan masuk ke rekening freelancer
          -> Ketika masuk cancel order maka pengguna dapat memilih dari pesanan yang masuk dari user untuk dibatalkan, jika dibatalkan maka user yang                     memesan mendpatkan refund 100% dari harga yang dibayarkan dan freelancer tidak mendapat uang
          
      ->Ketika login sebagai user maka terdapat 4 menu yakni:
        1. view profile
        2. display services
        3. order
        4. top up
          -> Ketika masuk view profile tampilannya akan sama untuk kedua role (freelancer/user)
          -> Ketika masuk display services maka akan menampilkan jasa-jasa yang dimasukkan oleh freelancer
          -> Ketika masuk order maka pengguna ditampilkan jasa-jasa yang tersedia kemudian memilih jasa mana yang ingin dipesan
          -> Ketika masuk top up maka pengguna memasukkan jumlah uang yang diinginkan
