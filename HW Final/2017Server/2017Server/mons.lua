myid = 9999;

function set_uid(x)
	myid= x;
return myid;
end

function player_move_notify(pid)
   player_x = API_get_x(pid);
   player_y = API_get_y(pid);
   my_x = API_get_x(myid);
   my_y = API_get_y(myid);
   bye = API_bye(myid);

   if (bye > 2  ) then
		API_SendMessage(myid, pid, "GOOD BYE");
   elseif (player_x == my_x) then
     if (player_y == my_y) then
        API_SendMessage(myid, pid, "HELLO");
     end
   end
end