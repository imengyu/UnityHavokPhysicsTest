using UnityEngine;
using PhyicsRT;
using UnityEngine.EventSystems;

public class Test : MonoBehaviour {

    Camera mainCamera;
    public float cameraSpeed = 4;
    public float shootForce = 100;
    public GameObject ballPrefab = null;

    private void Start() {  
        mainCamera = GetComponent<Camera>();
    }
    private void Update() {
        //空格键抬升高度
        if (Input.GetKey(KeyCode.Q))
        {
            transform.Translate(Vector3.up * cameraSpeed * Time.deltaTime, Space.Self);
        }
        if (Input.GetKey(KeyCode.E))
        {
            transform.Translate(Vector3.down * cameraSpeed * Time.deltaTime, Space.Self);
        }
        //w键
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow))
        {
            this.gameObject.transform.Translate(new Vector3(0, 0, 2 * cameraSpeed * Time.deltaTime));
        }
        //s键
        if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow))
        {
            this.gameObject.transform.Translate(new Vector3(0, 0, 2 * -cameraSpeed * Time.deltaTime));
        }
        //a键
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
        {
            this.gameObject.transform.Translate(new Vector3(-(cameraSpeed) * Time.deltaTime, 0, 0));
        }
        //d键
        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow) )
        {
            this.gameObject.transform.Translate(new Vector3((cameraSpeed) * Time.deltaTime, 0, 0));
        }

        //Zoom out
        if (Input.GetAxis("Mouse ScrollWheel") < 0)
        {
            if (cameraSpeed < 1)
                cameraSpeed -= 0.01f;
            else if (cameraSpeed < 10)
                cameraSpeed -= 0.1f;
            else if (cameraSpeed < 50)
                cameraSpeed -= 1f;
            else if (cameraSpeed < 100)
                cameraSpeed -= 5f;
            else cameraSpeed -= 10f;

            ShowText("Camera Speed : " + cameraSpeed);
        }
        //Zoom in
        if (Input.GetAxis("Mouse ScrollWheel") > 0)
        {
            if (cameraSpeed < 1)
                cameraSpeed += 0.01f;
            else if (cameraSpeed < 10)
                cameraSpeed += 0.1f;
            else if (cameraSpeed < 50)
                cameraSpeed += 1f;
            else if (cameraSpeed < 100)
                cameraSpeed += 5f;
            else cameraSpeed += 10f;

            ShowText("Camera Speed : " + cameraSpeed);
        }

        if (!EventSystem.current.IsPointerOverGameObject() && GUIUtility.hotControl == 0)
        {
            //左键按下事件
            //
            if (Input.GetMouseButtonDown(0) && !mouseLeftDowned)
            {
                Shoot(false);
                mouseLeftDowned = true;
            }
            if (Input.GetMouseButtonUp(0) && mouseLeftDowned)
                mouseLeftDowned = false;
        
        }
    }

    // UI Events
    //===============================

    Rect uiBoxRect = new Rect(12, 30, 200, 63);
    int textShowInt = 0;
    string textShow = "";

    private void ShowText(string text, int sec = 3)
    {
        textShow = text;
        textShowInt = sec * 60;
    }
    private void OnGUI()
    {
        GUI.Box(uiBoxRect, "");
        GUI.Label(new Rect(18, 36, 190, 46), "Camera : " + transform.position.ToString() + "\n" +
            transform.rotation.ToString() + "\n" +
             transform.eulerAngles.ToString());
        if (textShowInt > 0)
        {
            GUI.Label(new Rect(200, 15, 300, 30), textShow);
            textShowInt--;
        }
    }

    // Other
    //===============================
    
    bool mouseLeftDowned = false;

    public void Shoot(bool center)
    {
        ShowText("Shoot !");

        //获取鼠标点击位置
        //创建射线;从摄像机发射一条经过鼠标当前位置的射线

        Vector3 mousePos = Input.mousePosition;
        if (center) mousePos = new Vector3(Screen.width / 2, Screen.height / 2, 0);

        Ray ray = mainCamera.ScreenPointToRay(mousePos);
        
        //从摄像机的位置创建一个带有刚体的球ballPrefab为预制小球
        GameObject go = null;
        go = Instantiate(ballPrefab, transform.position, Quaternion.identity);
        go.transform.rotation = Random.rotation;

        //发射数来的球沿着摄像机到鼠标点击的方向进行移动
        PhysicsBody ball = go.GetComponent<PhysicsBody>();   
        ball.ApplyForce(shootForce * ray.direction);
    }
}