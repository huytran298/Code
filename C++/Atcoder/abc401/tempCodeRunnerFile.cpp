string s;
        cin >> s;
        
        if(s == "login"){
            status = true;
            continue;
        }
        if(s == "logout"){
            status = false;
            continue;
        }
        if(!status && s == "private"){
            cnt++;
            continue;
        }